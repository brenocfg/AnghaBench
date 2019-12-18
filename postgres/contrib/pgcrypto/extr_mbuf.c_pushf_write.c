#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {scalar_t__ block_size; int pos; int /*<<< orphan*/  const* buf; } ;
typedef  TYPE_1__ PushFilter ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int wrap_process (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

int
pushf_write(PushFilter *mp, const uint8 *data, int len)
{
	int			need,
				res;

	/*
	 * no buffering
	 */
	if (mp->block_size <= 0)
		return wrap_process(mp, data, len);

	/*
	 * try to empty buffer
	 */
	need = mp->block_size - mp->pos;
	if (need > 0)
	{
		if (len < need)
		{
			memcpy(mp->buf + mp->pos, data, len);
			mp->pos += len;
			return 0;
		}
		memcpy(mp->buf + mp->pos, data, need);
		len -= need;
		data += need;
	}

	/*
	 * buffer full, process
	 */
	res = wrap_process(mp, mp->buf, mp->block_size);
	if (res < 0)
		return res;
	mp->pos = 0;

	/*
	 * now process directly from data
	 */
	while (len > 0)
	{
		if (len > mp->block_size)
		{
			res = wrap_process(mp, data, mp->block_size);
			if (res < 0)
				return res;
			data += mp->block_size;
			len -= mp->block_size;
		}
		else
		{
			memcpy(mp->buf, data, len);
			mp->pos += len;
			break;
		}
	}
	return 0;
}