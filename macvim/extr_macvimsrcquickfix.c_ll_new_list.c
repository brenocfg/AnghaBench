#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  qf_refcount; } ;
typedef  TYPE_1__ qf_info_T ;

/* Variables and functions */
 scalar_t__ alloc (unsigned int) ; 
 int /*<<< orphan*/  vim_memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static qf_info_T *
ll_new_list()
{
    qf_info_T *qi;

    qi = (qf_info_T *)alloc((unsigned)sizeof(qf_info_T));
    if (qi != NULL)
    {
	vim_memset(qi, 0, (size_t)(sizeof(qf_info_T)));
	qi->qf_refcount++;
    }

    return qi;
}