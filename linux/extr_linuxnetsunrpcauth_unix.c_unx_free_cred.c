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
struct unx_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct unx_cred*) ; 
 int /*<<< orphan*/  kfree (struct unx_cred*) ; 

__attribute__((used)) static void
unx_free_cred(struct unx_cred *unx_cred)
{
	dprintk("RPC:       unx_free_cred %p\n", unx_cred);
	kfree(unx_cred);
}