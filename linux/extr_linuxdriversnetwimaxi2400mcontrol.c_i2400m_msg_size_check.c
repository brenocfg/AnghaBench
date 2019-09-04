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
struct i2400m_l3l4_hdr {int /*<<< orphan*/  type; int /*<<< orphan*/  length; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_l3l4_hdr const*,size_t,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,size_t,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

int i2400m_msg_size_check(struct i2400m *i2400m,
			  const struct i2400m_l3l4_hdr *l3l4_hdr,
			  size_t msg_size)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	size_t expected_size;
	d_fnstart(4, dev, "(i2400m %p l3l4_hdr %p msg_size %zu)\n",
		  i2400m, l3l4_hdr, msg_size);
	if (msg_size < sizeof(*l3l4_hdr)) {
		dev_err(dev, "bad size for message header "
			"(expected at least %zu, got %zu)\n",
			(size_t) sizeof(*l3l4_hdr), msg_size);
		result = -EIO;
		goto error_hdr_size;
	}
	expected_size = le16_to_cpu(l3l4_hdr->length) + sizeof(*l3l4_hdr);
	if (msg_size < expected_size) {
		dev_err(dev, "bad size for message code 0x%04x (expected %zu, "
			"got %zu)\n", le16_to_cpu(l3l4_hdr->type),
			expected_size, msg_size);
		result = -EIO;
	} else
		result = 0;
error_hdr_size:
	d_fnend(4, dev,
		"(i2400m %p l3l4_hdr %p msg_size %zu) = %d\n",
		i2400m, l3l4_hdr, msg_size, result);
	return result;
}