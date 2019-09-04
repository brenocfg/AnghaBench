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
struct nls_table {int (* uni2char ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  charset; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  NLS_MAX_CHARSET_SIZE ; 
 int SFM_MAP_UNI_RSVD ; 
 int SFU_MAP_UNI_RSVD ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 scalar_t__ convert_sfm_char (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ convert_sfu_char (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
cifs_mapchar(char *target, const __u16 *from, const struct nls_table *cp,
	     int maptype)
{
	int len = 1;
	__u16 src_char;

	src_char = *from;

	if ((maptype == SFM_MAP_UNI_RSVD) && convert_sfm_char(src_char, target))
		return len;
	else if ((maptype == SFU_MAP_UNI_RSVD) &&
		  convert_sfu_char(src_char, target))
		return len;

	/* if character not one of seven in special remap set */
	len = cp->uni2char(src_char, target, NLS_MAX_CHARSET_SIZE);
	if (len <= 0)
		goto surrogate_pair;

	return len;

surrogate_pair:
	/* convert SURROGATE_PAIR and IVS */
	if (strcmp(cp->charset, "utf8"))
		goto unknown;
	len = utf16s_to_utf8s(from, 3, UTF16_LITTLE_ENDIAN, target, 6);
	if (len <= 0)
		goto unknown;
	return len;

unknown:
	*target = '?';
	len = 1;
	return len;
}