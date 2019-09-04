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
typedef  size_t u8 ;
typedef  int u16 ;
struct il_tfd_tb {int /*<<< orphan*/  hi_n_len; } ;
struct il_tfd {struct il_tfd_tb* tbs; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16
il4965_tfd_tb_get_len(struct il_tfd *tfd, u8 idx)
{
	struct il_tfd_tb *tb = &tfd->tbs[idx];

	return le16_to_cpu(tb->hi_n_len) >> 4;
}