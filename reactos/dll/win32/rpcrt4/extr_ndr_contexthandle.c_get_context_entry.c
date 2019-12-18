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
struct context_handle_entry {scalar_t__ magic; } ;
typedef  struct context_handle_entry* NDR_CCONTEXT ;

/* Variables and functions */
 scalar_t__ NDR_CONTEXT_HANDLE_MAGIC ; 

__attribute__((used)) static struct context_handle_entry *get_context_entry(NDR_CCONTEXT CContext)
{
    struct context_handle_entry *che = CContext;

    if (che->magic != NDR_CONTEXT_HANDLE_MAGIC)
        return NULL;
    return che;
}