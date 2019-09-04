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
struct dcon_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcon_set_source (struct dcon_priv*,int) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 

__attribute__((used)) static void dcon_set_source_sync(struct dcon_priv *dcon, int arg)
{
	dcon_set_source(dcon, arg);
	flush_scheduled_work();
}