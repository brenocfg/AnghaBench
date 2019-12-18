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
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_doc_nsevent_handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * impl_from_DispatchEx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLDocumentNode_bind_event(DispatchEx *dispex, int eid)
{
    HTMLDocumentNode *This = impl_from_DispatchEx(dispex);
    ensure_doc_nsevent_handler(This, eid);
}