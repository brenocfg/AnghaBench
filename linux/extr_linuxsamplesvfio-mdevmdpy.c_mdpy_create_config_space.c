#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mdev_state {int* vconfig; int bar_mask; int memsize; TYPE_1__* type; } ;
struct TYPE_2__ {int format; int width; int height; } ;

/* Variables and functions */
 size_t MDPY_FORMAT_OFFSET ; 
 size_t MDPY_HEIGHT_OFFSET ; 
 int MDPY_PCI_DEVICE_ID ; 
 int MDPY_PCI_SUBDEVICE_ID ; 
 int MDPY_PCI_SUBVENDOR_ID ; 
 int MDPY_PCI_VENDOR_ID ; 
 int MDPY_VENDORCAP_OFFSET ; 
 int MDPY_VENDORCAP_SIZE ; 
 size_t MDPY_WIDTH_OFFSET ; 
 size_t PCI_BASE_ADDRESS_0 ; 
 int PCI_BASE_ADDRESS_MEM_PREFETCH ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_32 ; 
 int PCI_BASE_ADDRESS_SPACE_MEMORY ; 
 size_t PCI_CAPABILITY_LIST ; 
 size_t PCI_CLASS_DEVICE ; 
 int PCI_CLASS_DISPLAY_OTHER ; 
 size_t PCI_CLASS_REVISION ; 
 size_t PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 size_t PCI_DEVICE_ID ; 
 size_t PCI_STATUS ; 
 int PCI_STATUS_CAP_LIST ; 
 size_t PCI_SUBSYSTEM_ID ; 
 size_t PCI_SUBSYSTEM_VENDOR_ID ; 
 size_t PCI_VENDOR_ID ; 
 int /*<<< orphan*/  STORE_LE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STORE_LE32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mdpy_create_config_space(struct mdev_state *mdev_state)
{
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_VENDOR_ID],
		   MDPY_PCI_VENDOR_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_DEVICE_ID],
		   MDPY_PCI_DEVICE_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_VENDOR_ID],
		   MDPY_PCI_SUBVENDOR_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_ID],
		   MDPY_PCI_SUBDEVICE_ID);

	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_COMMAND],
		   PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_STATUS],
		   PCI_STATUS_CAP_LIST);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_CLASS_DEVICE],
		   PCI_CLASS_DISPLAY_OTHER);
	mdev_state->vconfig[PCI_CLASS_REVISION] =  0x01;

	STORE_LE32((u32 *) &mdev_state->vconfig[PCI_BASE_ADDRESS_0],
		   PCI_BASE_ADDRESS_SPACE_MEMORY |
		   PCI_BASE_ADDRESS_MEM_TYPE_32	 |
		   PCI_BASE_ADDRESS_MEM_PREFETCH);
	mdev_state->bar_mask = ~(mdev_state->memsize) + 1;

	/* vendor specific capability for the config registers */
	mdev_state->vconfig[PCI_CAPABILITY_LIST]       = MDPY_VENDORCAP_OFFSET;
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 0] = 0x09; /* vendor cap */
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 1] = 0x00; /* next ptr */
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 2] = MDPY_VENDORCAP_SIZE;
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_FORMAT_OFFSET],
		   mdev_state->type->format);
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_WIDTH_OFFSET],
		   mdev_state->type->width);
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_HEIGHT_OFFSET],
		   mdev_state->type->height);
}