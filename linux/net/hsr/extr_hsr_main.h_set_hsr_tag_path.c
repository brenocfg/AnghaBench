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
typedef  int u16 ;
struct hsr_tag {int /*<<< orphan*/  path_and_LSDU_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_hsr_tag_path(struct hsr_tag *ht, u16 path)
{
	ht->path_and_LSDU_size =
		htons((ntohs(ht->path_and_LSDU_size) & 0x0FFF) | (path << 12));
}