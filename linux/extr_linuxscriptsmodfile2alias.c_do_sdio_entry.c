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
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SDIO_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ class ; 
 scalar_t__ device ; 
 int /*<<< orphan*/  sdio_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vendor ; 

__attribute__((used)) static int do_sdio_entry(const char *filename,
			void *symval, char *alias)
{
	DEF_FIELD(symval, sdio_device_id, class);
	DEF_FIELD(symval, sdio_device_id, vendor);
	DEF_FIELD(symval, sdio_device_id, device);

	strcpy(alias, "sdio:");
	ADD(alias, "c", class != (__u8)SDIO_ANY_ID, class);
	ADD(alias, "v", vendor != (__u16)SDIO_ANY_ID, vendor);
	ADD(alias, "d", device != (__u16)SDIO_ANY_ID, device);
	add_wildcard(alias);
	return 1;
}