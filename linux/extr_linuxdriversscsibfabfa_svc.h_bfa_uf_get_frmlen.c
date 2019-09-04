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
struct bfa_uf_s {int /*<<< orphan*/  data_len; } ;

/* Variables and functions */

__attribute__((used)) static inline   u16
bfa_uf_get_frmlen(struct bfa_uf_s *uf)
{
	return uf->data_len;
}