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
typedef  int /*<<< orphan*/  uint16_t ;
struct tpm_buf {size_t len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void store16(struct tpm_buf *buf, const uint16_t value)
{
	*(uint16_t *) & buf->data[buf->len] = htons(value);
	buf->len += sizeof value;
}