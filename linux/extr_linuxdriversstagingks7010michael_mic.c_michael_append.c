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
typedef  int /*<<< orphan*/  u8 ;
struct michael_mic {int m_bytes; int /*<<< orphan*/ * m; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  michael_block (struct michael_mic*) ; 

__attribute__((used)) static void michael_append(struct michael_mic *mic, u8 *src, int bytes)
{
	int addlen;

	if (mic->m_bytes) {
		addlen = 4 - mic->m_bytes;
		if (addlen > bytes)
			addlen = bytes;
		memcpy(&mic->m[mic->m_bytes], src, addlen);
		mic->m_bytes += addlen;
		src += addlen;
		bytes -= addlen;

		if (mic->m_bytes < 4)
			return;

		mic->l ^= get_unaligned_le32(mic->m);
		michael_block(mic);
		mic->m_bytes = 0;
	}

	while (bytes >= 4) {
		mic->l ^= get_unaligned_le32(src);
		michael_block(mic);
		src += 4;
		bytes -= 4;
	}

	if (bytes > 0) {
		mic->m_bytes = bytes;
		memcpy(mic->m, src, bytes);
	}
}