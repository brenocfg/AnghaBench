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
typedef  int /*<<< orphan*/  u32 ;
struct ar5523 {int dummy; } ;

/* Variables and functions */
 int AR5523_CMD_FLAG_READ ; 
 int ar5523_cmd (struct ar5523*,int /*<<< orphan*/ ,void const*,int,void*,int,int) ; 

__attribute__((used)) static int ar5523_cmd_read(struct ar5523 *ar, u32 code, const void *idata,
			   int ilen, void *odata, int olen, int flags)
{
	flags |= AR5523_CMD_FLAG_READ;
	return ar5523_cmd(ar, code, idata, ilen, odata, olen, flags);
}