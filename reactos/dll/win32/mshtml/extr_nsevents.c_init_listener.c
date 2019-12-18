#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMEventListenerVtbl ;
struct TYPE_4__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * This; TYPE_1__ nsIDOMEventListener_iface; } ;
typedef  TYPE_2__ nsEventListener ;
typedef  int /*<<< orphan*/  nsDocumentEventListener ;

/* Variables and functions */

__attribute__((used)) static void init_listener(nsEventListener *This, nsDocumentEventListener *listener,
        const nsIDOMEventListenerVtbl *vtbl)
{
    This->nsIDOMEventListener_iface.lpVtbl = vtbl;
    This->This = listener;
}