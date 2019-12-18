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

/* Variables and functions */
#define  CHAR_LITERAL 134 
#define  CXX_COMMENT 133 
#define  C_COMMENT 132 
#define  FINISHING_COMMENT 131 
 int /*<<< orphan*/  LS_DIRTY ; 
 int /*<<< orphan*/  LS_START ; 
#define  NO_COMMENT 130 
#define  STARTING_COMMENT 129 
#define  STRING_LITERAL 128 
 int /*<<< orphan*/  abort () ; 
 size_t depth ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__* ignoring ; 
 int incomment ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  linestate ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ text ; 

__attribute__((used)) static const char *
skipcomment(const char *cp)
{
	if (text || ignoring[depth]) {
		for (; isspace((unsigned char)*cp); cp++)
			if (*cp == '\n')
				linestate = LS_START;
		return (cp);
	}
	while (*cp != '\0')
		/* don't reset to LS_START after a line continuation */
		if (strncmp(cp, "\\\r\n", 3) == 0)
			cp += 3;
		else if (strncmp(cp, "\\\n", 2) == 0)
			cp += 2;
		else switch (incomment) {
		case NO_COMMENT:
			if (strncmp(cp, "/\\\r\n", 4) == 0) {
				incomment = STARTING_COMMENT;
				cp += 4;
			} else if (strncmp(cp, "/\\\n", 3) == 0) {
				incomment = STARTING_COMMENT;
				cp += 3;
			} else if (strncmp(cp, "/*", 2) == 0) {
				incomment = C_COMMENT;
				cp += 2;
			} else if (strncmp(cp, "//", 2) == 0) {
				incomment = CXX_COMMENT;
				cp += 2;
			} else if (strncmp(cp, "\'", 1) == 0) {
				incomment = CHAR_LITERAL;
				linestate = LS_DIRTY;
				cp += 1;
			} else if (strncmp(cp, "\"", 1) == 0) {
				incomment = STRING_LITERAL;
				linestate = LS_DIRTY;
				cp += 1;
			} else if (strncmp(cp, "\n", 1) == 0) {
				linestate = LS_START;
				cp += 1;
			} else if (strchr(" \r\t", *cp) != NULL) {
				cp += 1;
			} else
				return (cp);
			continue;
		case CXX_COMMENT:
			if (strncmp(cp, "\n", 1) == 0) {
				incomment = NO_COMMENT;
				linestate = LS_START;
			}
			cp += 1;
			continue;
		case CHAR_LITERAL:
		case STRING_LITERAL:
			if ((incomment == CHAR_LITERAL && cp[0] == '\'') ||
			    (incomment == STRING_LITERAL && cp[0] == '\"')) {
				incomment = NO_COMMENT;
				cp += 1;
			} else if (cp[0] == '\\') {
				if (cp[1] == '\0')
					cp += 1;
				else
					cp += 2;
			} else if (strncmp(cp, "\n", 1) == 0) {
				if (incomment == CHAR_LITERAL)
					error("unterminated char literal");
				else
					error("unterminated string literal");
			} else
				cp += 1;
			continue;
		case C_COMMENT:
			if (strncmp(cp, "*\\\r\n", 4) == 0) {
				incomment = FINISHING_COMMENT;
				cp += 4;
			} else if (strncmp(cp, "*\\\n", 3) == 0) {
				incomment = FINISHING_COMMENT;
				cp += 3;
			} else if (strncmp(cp, "*/", 2) == 0) {
				incomment = NO_COMMENT;
				cp += 2;
			} else
				cp += 1;
			continue;
		case STARTING_COMMENT:
			if (*cp == '*') {
				incomment = C_COMMENT;
				cp += 1;
			} else if (*cp == '/') {
				incomment = CXX_COMMENT;
				cp += 1;
			} else {
				incomment = NO_COMMENT;
				linestate = LS_DIRTY;
			}
			continue;
		case FINISHING_COMMENT:
			if (*cp == '/') {
				incomment = NO_COMMENT;
				cp += 1;
			} else
				incomment = C_COMMENT;
			continue;
		default:
			abort(); /* bug */
		}
	return (cp);
}