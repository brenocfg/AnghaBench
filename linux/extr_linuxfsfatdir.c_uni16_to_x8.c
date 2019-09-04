#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct super_block {int dummy; } ;
struct nls_table {int (* uni2char ) (int,unsigned char*,int) ;} ;
struct TYPE_3__ {int unicode_xlate; } ;
struct TYPE_4__ {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 int NLS_MAX_CHARSET_SIZE ; 
 int /*<<< orphan*/  fat_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 unsigned char* hex_byte_pack (unsigned char*,int) ; 
 int stub1 (int,unsigned char*,int) ; 
 scalar_t__ unlikely (int const) ; 

__attribute__((used)) static int uni16_to_x8(struct super_block *sb, unsigned char *ascii,
		       const wchar_t *uni, int len, struct nls_table *nls)
{
	int uni_xlate = MSDOS_SB(sb)->options.unicode_xlate;
	const wchar_t *ip;
	wchar_t ec;
	unsigned char *op;
	int charlen;

	ip = uni;
	op = ascii;

	while (*ip && ((len - NLS_MAX_CHARSET_SIZE) > 0)) {
		ec = *ip++;
		charlen = nls->uni2char(ec, op, NLS_MAX_CHARSET_SIZE);
		if (charlen > 0) {
			op += charlen;
			len -= charlen;
		} else {
			if (uni_xlate == 1) {
				*op++ = ':';
				op = hex_byte_pack(op, ec >> 8);
				op = hex_byte_pack(op, ec);
				len -= 5;
			} else {
				*op++ = '?';
				len--;
			}
		}
	}

	if (unlikely(*ip)) {
		fat_msg(sb, KERN_WARNING,
			"filename was truncated while converting.");
	}

	*op = 0;
	return op - ascii;
}