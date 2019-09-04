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
struct r_magic {int type; int str_flags; int str_range; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ RMagic ;

/* Variables and functions */
 int CHAR_COMPACT_BLANK ; 
 int CHAR_COMPACT_OPTIONAL_BLANK ; 
 int CHAR_REGEX_OFFSET_START ; 
#define  FILE_BESTRING16 133 
#define  FILE_LESTRING16 132 
#define  FILE_PSTRING 131 
#define  FILE_REGEX 130 
#define  FILE_SEARCH 129 
#define  FILE_STRING 128 
 int REGEX_OFFSET_START ; 
 int R_MAGIC_CHECK ; 
 int STRING_COMPACT_BLANK ; 
 int STRING_COMPACT_OPTIONAL_BLANK ; 
 int STRING_DEFAULT_RANGE ; 
 int /*<<< orphan*/  file_magwarn (TYPE_1__*,char*,...) ; 

__attribute__((used)) static int string_modifier_check(RMagic *ms, struct r_magic *m) {
	if ((ms->flags & R_MAGIC_CHECK) == 0) {
		return 0;
	}

	switch (m->type) {
	case FILE_BESTRING16:
	case FILE_LESTRING16:
		if (m->str_flags != 0) {
			file_magwarn(ms,
			    "no modifiers allowed for 16-bit strings\n");
			return -1;
		}
		break;
	case FILE_STRING:
	case FILE_PSTRING:
		if ((m->str_flags & REGEX_OFFSET_START) != 0) {
			file_magwarn(ms,
			    "'/%c' only allowed on regex and search\n",
			    CHAR_REGEX_OFFSET_START);
			return -1;
		}
		break;
	case FILE_SEARCH:
		if (m->str_range == 0) {
			file_magwarn(ms,
			    "missing range; defaulting to %d\n",
                            STRING_DEFAULT_RANGE);
			m->str_range = STRING_DEFAULT_RANGE;
			return -1;
		}
		break;
	case FILE_REGEX:
		if ((m->str_flags & STRING_COMPACT_BLANK) != 0) {
			file_magwarn(ms, "'/%c' not allowed on regex\n",
			    CHAR_COMPACT_BLANK);
			return -1;
		}
		if ((m->str_flags & STRING_COMPACT_OPTIONAL_BLANK) != 0) {
			file_magwarn(ms, "'/%c' not allowed on regex\n",
			    CHAR_COMPACT_OPTIONAL_BLANK);
			return -1;
		}
		break;
	default:
		file_magwarn (ms, "coding error: m->type=%d\n",
		    m->type);
		return -1;
	}
	return 0;
}