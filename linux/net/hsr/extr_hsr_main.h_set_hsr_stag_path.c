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
 int /*<<< orphan*/  set_hsr_tag_path (struct hsr_tag*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_hsr_stag_path(struct hsr_sup_tag *hst, u16 path)
{
	set_hsr_tag_path((struct hsr_tag *)hst, path);
}