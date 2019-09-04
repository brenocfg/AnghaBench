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
typedef  int u32 ;
struct sigma_action {int len_hi; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 sigma_action_len(struct sigma_action *sa)
{
	return (sa->len_hi << 16) | le16_to_cpu(sa->len);
}