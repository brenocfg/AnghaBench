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
struct i2400m {int /*<<< orphan*/ * bm_cmd_buf; int /*<<< orphan*/ * bm_ack_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2400M_BM_ACK_BUF_SIZE ; 
 int /*<<< orphan*/  I2400M_BM_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int i2400m_bm_buf_alloc(struct i2400m *i2400m)
{
	int result;

	result = -ENOMEM;
	i2400m->bm_cmd_buf = kzalloc(I2400M_BM_CMD_BUF_SIZE, GFP_KERNEL);
	if (i2400m->bm_cmd_buf == NULL)
		goto error_bm_cmd_kzalloc;
	i2400m->bm_ack_buf = kzalloc(I2400M_BM_ACK_BUF_SIZE, GFP_KERNEL);
	if (i2400m->bm_ack_buf == NULL)
		goto error_bm_ack_buf_kzalloc;
	return 0;

error_bm_ack_buf_kzalloc:
	kfree(i2400m->bm_cmd_buf);
error_bm_cmd_kzalloc:
	return result;
}