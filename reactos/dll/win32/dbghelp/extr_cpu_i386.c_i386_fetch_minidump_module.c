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
struct dump_context {int dummy; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static BOOL i386_fetch_minidump_module(struct dump_context* dc, unsigned index, unsigned flags)
{
    /* FIXME: actually, we should probably take care of FPO data, unless it's stored in
     * function table minidump stream
     */
    return FALSE;
}