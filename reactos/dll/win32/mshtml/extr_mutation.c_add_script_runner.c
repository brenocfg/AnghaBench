#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  runnable_proc_t ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_3__ nsIRunnable_iface; int /*<<< orphan*/ * arg2; int /*<<< orphan*/ * arg1; int /*<<< orphan*/  proc; TYPE_2__* doc; } ;
typedef  TYPE_1__ nsRunnable ;
typedef  int /*<<< orphan*/  nsISupports ;
struct TYPE_8__ {int /*<<< orphan*/  basedoc; } ;
typedef  TYPE_2__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  content_utils ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  htmldoc_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentUtils_AddScriptRunner (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nsIRunnable_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  nsISupports_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsRunnableVtbl ; 

__attribute__((used)) static void add_script_runner(HTMLDocumentNode *This, runnable_proc_t proc, nsISupports *arg1, nsISupports *arg2)
{
    nsRunnable *runnable;

    runnable = heap_alloc_zero(sizeof(*runnable));
    if(!runnable)
        return;

    runnable->nsIRunnable_iface.lpVtbl = &nsRunnableVtbl;
    runnable->ref = 1;

    htmldoc_addref(&This->basedoc);
    runnable->doc = This;
    runnable->proc = proc;

    if(arg1)
        nsISupports_AddRef(arg1);
    runnable->arg1 = arg1;

    if(arg2)
        nsISupports_AddRef(arg2);
    runnable->arg2 = arg2;

    nsIContentUtils_AddScriptRunner(content_utils, &runnable->nsIRunnable_iface);

    nsIRunnable_Release(&runnable->nsIRunnable_iface);
}