#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_1__ sha256; } ;
struct TYPE_7__ {TYPE_2__ state; } ;
typedef  TYPE_3__ lzma_check_state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

extern void
lzma_sha256_init(lzma_check_state *check)
{
	static const uint32_t s[8] = {
		0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
		0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19,
	};

	memcpy(check->state.sha256.state, s, sizeof(s));
	check->state.sha256.size = 0;

	return;
}