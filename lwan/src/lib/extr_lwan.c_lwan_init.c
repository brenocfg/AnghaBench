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
struct lwan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_config ; 
 int /*<<< orphan*/  lwan_init_with_config (struct lwan*,int /*<<< orphan*/ *) ; 

void lwan_init(struct lwan *l) { lwan_init_with_config(l, &default_config); }