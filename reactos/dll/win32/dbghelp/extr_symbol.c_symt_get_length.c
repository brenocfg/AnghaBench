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
struct symt {int dummy; } ;
struct module {int dummy; } ;
typedef  int ULONG64 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TI_GET_LENGTH ; 
 int /*<<< orphan*/  TI_GET_TYPE ; 
 scalar_t__ symt_get_info (struct module*,struct symt const*,int /*<<< orphan*/ ,int*) ; 
 struct symt const* symt_index2ptr (struct module*,int) ; 

__attribute__((used)) static void symt_get_length(struct module* module, const struct symt* symt, ULONG64* size)
{
    DWORD       type_index;

    if (symt_get_info(module,  symt, TI_GET_LENGTH, size) && *size)
        return;

    if (symt_get_info(module, symt, TI_GET_TYPE, &type_index) &&
        symt_get_info(module, symt_index2ptr(module, type_index), TI_GET_LENGTH, size)) return;
    *size = 0x1000; /* arbitrary value */
}