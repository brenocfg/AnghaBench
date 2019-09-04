#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct hfsplus_wd {int ablk_size; int embed_start; int embed_count; void* ablk_start; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int HFSPLUS_SECTOR_SIZE ; 
 int /*<<< orphan*/  HFSPLUS_VOLHEAD_SIG ; 
 int /*<<< orphan*/  HFSPLUS_VOLHEAD_SIGX ; 
 int HFSP_WRAPOFF_ABLKSIZE ; 
 int HFSP_WRAPOFF_ABLKSTART ; 
 int HFSP_WRAPOFF_ATTRIB ; 
 int HFSP_WRAPOFF_EMBEDEXT ; 
 int HFSP_WRAPOFF_EMBEDSIG ; 
 int HFSP_WRAP_ATTRIB_SLOCK ; 
 int HFSP_WRAP_ATTRIB_SPARED ; 
 void* be16_to_cpu (scalar_t__) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int get_unaligned_be32 (void*) ; 

__attribute__((used)) static int hfsplus_read_mdb(void *bufptr, struct hfsplus_wd *wd)
{
	u32 extent;
	u16 attrib;
	__be16 sig;

	sig = *(__be16 *)(bufptr + HFSP_WRAPOFF_EMBEDSIG);
	if (sig != cpu_to_be16(HFSPLUS_VOLHEAD_SIG) &&
	    sig != cpu_to_be16(HFSPLUS_VOLHEAD_SIGX))
		return 0;

	attrib = be16_to_cpu(*(__be16 *)(bufptr + HFSP_WRAPOFF_ATTRIB));
	if (!(attrib & HFSP_WRAP_ATTRIB_SLOCK) ||
	   !(attrib & HFSP_WRAP_ATTRIB_SPARED))
		return 0;

	wd->ablk_size =
		be32_to_cpu(*(__be32 *)(bufptr + HFSP_WRAPOFF_ABLKSIZE));
	if (wd->ablk_size < HFSPLUS_SECTOR_SIZE)
		return 0;
	if (wd->ablk_size % HFSPLUS_SECTOR_SIZE)
		return 0;
	wd->ablk_start =
		be16_to_cpu(*(__be16 *)(bufptr + HFSP_WRAPOFF_ABLKSTART));

	extent = get_unaligned_be32(bufptr + HFSP_WRAPOFF_EMBEDEXT);
	wd->embed_start = (extent >> 16) & 0xFFFF;
	wd->embed_count = extent & 0xFFFF;

	return 1;
}