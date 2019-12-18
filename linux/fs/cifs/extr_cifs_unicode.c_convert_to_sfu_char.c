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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_ASTERISK ; 
 int /*<<< orphan*/  UNI_COLON ; 
 int /*<<< orphan*/  UNI_GRTRTHAN ; 
 int /*<<< orphan*/  UNI_LESSTHAN ; 
 int /*<<< orphan*/  UNI_PIPE ; 
 int /*<<< orphan*/  UNI_QUESTION ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le16 convert_to_sfu_char(char src_char)
{
	__le16 dest_char;

	switch (src_char) {
	case ':':
		dest_char = cpu_to_le16(UNI_COLON);
		break;
	case '*':
		dest_char = cpu_to_le16(UNI_ASTERISK);
		break;
	case '?':
		dest_char = cpu_to_le16(UNI_QUESTION);
		break;
	case '<':
		dest_char = cpu_to_le16(UNI_LESSTHAN);
		break;
	case '>':
		dest_char = cpu_to_le16(UNI_GRTRTHAN);
		break;
	case '|':
		dest_char = cpu_to_le16(UNI_PIPE);
		break;
	default:
		dest_char = 0;
	}

	return dest_char;
}