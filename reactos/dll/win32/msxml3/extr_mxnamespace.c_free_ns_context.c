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
struct nscontext {int count; struct nscontext* ns; int /*<<< orphan*/  uri; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct nscontext*) ; 

__attribute__((used)) static void free_ns_context(struct nscontext *ctxt)
{
    int i;

    for (i = 0; i < ctxt->count; i++)
    {
        SysFreeString(ctxt->ns[i].prefix);
        SysFreeString(ctxt->ns[i].uri);
    }

    heap_free(ctxt->ns);
    heap_free(ctxt);
}