#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int check_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_buf_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load(RBinFile *bf) {
	ut64 sz;
	const ut8 *bytes = r_buf_buffer (bf->buf, &sz);
	return check_bytes (bytes, sz);
}