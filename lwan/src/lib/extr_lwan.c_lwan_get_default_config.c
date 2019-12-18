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
struct lwan_config {int dummy; } ;

/* Variables and functions */
 struct lwan_config const default_config ; 

const struct lwan_config *lwan_get_default_config(void)
{
    return &default_config;
}