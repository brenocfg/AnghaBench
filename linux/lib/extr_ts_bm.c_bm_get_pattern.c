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
struct ts_config {int dummy; } ;
struct ts_bm {void* pattern; } ;

/* Variables and functions */
 struct ts_bm* ts_config_priv (struct ts_config*) ; 

__attribute__((used)) static void *bm_get_pattern(struct ts_config *conf)
{
	struct ts_bm *bm = ts_config_priv(conf);
	return bm->pattern;
}