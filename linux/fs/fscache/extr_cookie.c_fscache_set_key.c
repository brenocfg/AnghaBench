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
typedef  scalar_t__ u32 ;
struct fscache_cookie {unsigned long long key_hash; scalar_t__ type; scalar_t__ parent; scalar_t__ inline_key; scalar_t__* key; } ;

/* Variables and functions */
 int DIV_ROUND_UP (size_t,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void const*,size_t) ; 

__attribute__((used)) static int fscache_set_key(struct fscache_cookie *cookie,
			   const void *index_key, size_t index_key_len)
{
	unsigned long long h;
	u32 *buf;
	int bufs;
	int i;

	bufs = DIV_ROUND_UP(index_key_len, sizeof(*buf));

	if (index_key_len > sizeof(cookie->inline_key)) {
		buf = kcalloc(bufs, sizeof(*buf), GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		cookie->key = buf;
	} else {
		buf = (u32 *)cookie->inline_key;
	}

	memcpy(buf, index_key, index_key_len);

	/* Calculate a hash and combine this with the length in the first word
	 * or first half word
	 */
	h = (unsigned long)cookie->parent;
	h += index_key_len + cookie->type;

	for (i = 0; i < bufs; i++)
		h += buf[i];

	cookie->key_hash = h ^ (h >> 32);
	return 0;
}