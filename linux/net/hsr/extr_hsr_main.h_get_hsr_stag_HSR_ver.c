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
typedef  int /*<<< orphan*/  u16 ;
struct hsr_tag {int dummy; } ;
struct hsr_sup_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_hsr_tag_LSDU_size (struct hsr_tag*) ; 

__attribute__((used)) static inline u16 get_hsr_stag_HSR_ver(struct hsr_sup_tag *hst)
{
	return get_hsr_tag_LSDU_size((struct hsr_tag *)hst);
}