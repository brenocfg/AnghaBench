#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  uintptr_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mpt3sas_nvme_cmd {int /*<<< orphan*/  prp2; int /*<<< orphan*/  prp1; } ;
struct MPT3SAS_ADAPTER {int page_size; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_3__ {scalar_t__ NVMe_Command; } ;
typedef  TYPE_1__ Mpi26NVMeEncapsulatedRequest_t ;

/* Variables and functions */
 int NVME_PRP_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 scalar_t__ mpt3sas_base_get_pcie_sgl (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int mpt3sas_base_get_pcie_sgl_dma (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_base_build_nvme_prp(struct MPT3SAS_ADAPTER *ioc, u16 smid,
	Mpi26NVMeEncapsulatedRequest_t *nvme_encap_request,
	dma_addr_t data_out_dma, size_t data_out_sz, dma_addr_t data_in_dma,
	size_t data_in_sz)
{
	int		prp_size = NVME_PRP_SIZE;
	__le64		*prp_entry, *prp1_entry, *prp2_entry;
	__le64		*prp_page;
	dma_addr_t	prp_entry_dma, prp_page_dma, dma_addr;
	u32		offset, entry_len;
	u32		page_mask_result, page_mask;
	size_t		length;
	struct mpt3sas_nvme_cmd *nvme_cmd =
		(void *)nvme_encap_request->NVMe_Command;

	/*
	 * Not all commands require a data transfer. If no data, just return
	 * without constructing any PRP.
	 */
	if (!data_in_sz && !data_out_sz)
		return;
	prp1_entry = &nvme_cmd->prp1;
	prp2_entry = &nvme_cmd->prp2;
	prp_entry = prp1_entry;
	/*
	 * For the PRP entries, use the specially allocated buffer of
	 * contiguous memory.
	 */
	prp_page = (__le64 *)mpt3sas_base_get_pcie_sgl(ioc, smid);
	prp_page_dma = mpt3sas_base_get_pcie_sgl_dma(ioc, smid);

	/*
	 * Check if we are within 1 entry of a page boundary we don't
	 * want our first entry to be a PRP List entry.
	 */
	page_mask = ioc->page_size - 1;
	page_mask_result = (uintptr_t)((u8 *)prp_page + prp_size) & page_mask;
	if (!page_mask_result) {
		/* Bump up to next page boundary. */
		prp_page = (__le64 *)((u8 *)prp_page + prp_size);
		prp_page_dma = prp_page_dma + prp_size;
	}

	/*
	 * Set PRP physical pointer, which initially points to the current PRP
	 * DMA memory page.
	 */
	prp_entry_dma = prp_page_dma;

	/* Get physical address and length of the data buffer. */
	if (data_in_sz) {
		dma_addr = data_in_dma;
		length = data_in_sz;
	} else {
		dma_addr = data_out_dma;
		length = data_out_sz;
	}

	/* Loop while the length is not zero. */
	while (length) {
		/*
		 * Check if we need to put a list pointer here if we are at
		 * page boundary - prp_size (8 bytes).
		 */
		page_mask_result = (prp_entry_dma + prp_size) & page_mask;
		if (!page_mask_result) {
			/*
			 * This is the last entry in a PRP List, so we need to
			 * put a PRP list pointer here.  What this does is:
			 *   - bump the current memory pointer to the next
			 *     address, which will be the next full page.
			 *   - set the PRP Entry to point to that page.  This
			 *     is now the PRP List pointer.
			 *   - bump the PRP Entry pointer the start of the
			 *     next page.  Since all of this PRP memory is
			 *     contiguous, no need to get a new page - it's
			 *     just the next address.
			 */
			prp_entry_dma++;
			*prp_entry = cpu_to_le64(prp_entry_dma);
			prp_entry++;
		}

		/* Need to handle if entry will be part of a page. */
		offset = dma_addr & page_mask;
		entry_len = ioc->page_size - offset;

		if (prp_entry == prp1_entry) {
			/*
			 * Must fill in the first PRP pointer (PRP1) before
			 * moving on.
			 */
			*prp1_entry = cpu_to_le64(dma_addr);

			/*
			 * Now point to the second PRP entry within the
			 * command (PRP2).
			 */
			prp_entry = prp2_entry;
		} else if (prp_entry == prp2_entry) {
			/*
			 * Should the PRP2 entry be a PRP List pointer or just
			 * a regular PRP pointer?  If there is more than one
			 * more page of data, must use a PRP List pointer.
			 */
			if (length > ioc->page_size) {
				/*
				 * PRP2 will contain a PRP List pointer because
				 * more PRP's are needed with this command. The
				 * list will start at the beginning of the
				 * contiguous buffer.
				 */
				*prp2_entry = cpu_to_le64(prp_entry_dma);

				/*
				 * The next PRP Entry will be the start of the
				 * first PRP List.
				 */
				prp_entry = prp_page;
			} else {
				/*
				 * After this, the PRP Entries are complete.
				 * This command uses 2 PRP's and no PRP list.
				 */
				*prp2_entry = cpu_to_le64(dma_addr);
			}
		} else {
			/*
			 * Put entry in list and bump the addresses.
			 *
			 * After PRP1 and PRP2 are filled in, this will fill in
			 * all remaining PRP entries in a PRP List, one per
			 * each time through the loop.
			 */
			*prp_entry = cpu_to_le64(dma_addr);
			prp_entry++;
			prp_entry_dma++;
		}

		/*
		 * Bump the phys address of the command's data buffer by the
		 * entry_len.
		 */
		dma_addr += entry_len;

		/* Decrement length accounting for last partial page. */
		if (entry_len > length)
			length = 0;
		else
			length -= entry_len;
	}
}