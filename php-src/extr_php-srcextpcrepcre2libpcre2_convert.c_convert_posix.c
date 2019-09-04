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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  pcre2_convert_context ;
typedef  int /*<<< orphan*/  PCRE2_UCHAR ;
typedef  scalar_t__* PCRE2_SPTR ;
typedef  int PCRE2_SIZE ;
typedef  int BOOL ;

/* Variables and functions */
#define  CHAR_ASTERISK 143 
#define  CHAR_BACKSLASH 142 
#define  CHAR_CIRCUMFLEX_ACCENT 141 
 scalar_t__ CHAR_COLON ; 
#define  CHAR_DOLLAR_SIGN 140 
#define  CHAR_DOT 139 
#define  CHAR_LEFT_CURLY_BRACKET 138 
#define  CHAR_LEFT_PARENTHESIS 137 
#define  CHAR_LEFT_SQUARE_BRACKET 136 
#define  CHAR_PLUS 135 
#define  CHAR_QUESTION_MARK 134 
#define  CHAR_RIGHT_CURLY_BRACKET 133 
#define  CHAR_RIGHT_PARENTHESIS 132 
 scalar_t__ CHAR_RIGHT_SQUARE_BRACKET ; 
#define  CHAR_VERTICAL_LINE 131 
 int /*<<< orphan*/  CU2BYTES (int) ; 
 int FALSE ; 
 scalar_t__ PCRE2_CONVERT_POSIX_EXTENDED ; 
 int PCRE2_ERROR_END_BACKSLASH ; 
 int PCRE2_ERROR_MISSING_SQUARE_BRACKET ; 
 int PCRE2_ERROR_NOMEMORY ; 
 scalar_t__ POSIX_ANCHORED ; 
#define  POSIX_CLASS_NOT_STARTED 130 
#define  POSIX_CLASS_STARTED 129 
#define  POSIX_CLASS_STARTING 128 
 scalar_t__ POSIX_NOT_BRACKET ; 
 scalar_t__ POSIX_START_REGEX ; 
 int /*<<< orphan*/  PUTCHARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STR_BACKSLASH ; 
 int /*<<< orphan*/  STR_CIRCUMFLEX_ACCENT ; 
 int /*<<< orphan*/  STR_COLON_RIGHT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  STR_LEFT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  STR_RIGHT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  STR_STAR_NUL ; 
 int TRUE ; 
 int /*<<< orphan*/  isdigit (scalar_t__) ; 
 int /*<<< orphan*/  islower (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcre2_escaped_literals ; 
 int /*<<< orphan*/  posix_meta_escapes ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
convert_posix(uint32_t pattype, PCRE2_SPTR pattern, PCRE2_SIZE plength,
  BOOL utf, PCRE2_UCHAR *use_buffer, PCRE2_SIZE use_length,
  PCRE2_SIZE *bufflenptr, BOOL dummyrun, pcre2_convert_context *ccontext)
{
char *s;
PCRE2_SPTR posix = pattern;
PCRE2_UCHAR *p = use_buffer;
PCRE2_UCHAR *pp = p;
PCRE2_UCHAR *endp = p + use_length - 1;  /* Allow for trailing zero */
PCRE2_SIZE convlength = 0;

uint32_t bracount = 0;
uint32_t posix_state = POSIX_START_REGEX;
uint32_t lastspecial = 0;
BOOL extended = (pattype & PCRE2_CONVERT_POSIX_EXTENDED) != 0;
BOOL nextisliteral = FALSE;

(void)utf;       /* Not used when Unicode not supported */
(void)ccontext;  /* Not currently used */

/* Initialize default for error offset as end of input. */

*bufflenptr = plength;
PUTCHARS(STR_STAR_NUL);

/* Now scan the input. */

while (plength > 0)
  {
  uint32_t c, sc;
  int clength = 1;

  /* Add in the length of the last item, then, if in the dummy run, pull the
  pointer back to the start of the (temporary) buffer and then remember the
  start of the next item. */

  convlength += p - pp;
  if (dummyrun) p = use_buffer;
  pp = p;

  /* Pick up the next character */

#ifndef SUPPORT_UNICODE
  c = *posix;
#else
  GETCHARLENTEST(c, posix, clength);
#endif
  posix += clength;
  plength -= clength;

  sc = nextisliteral? 0 : c;
  nextisliteral = FALSE;

  /* Handle a character within a class. */

  if (posix_state >= POSIX_CLASS_NOT_STARTED)
    {
    if (c == CHAR_RIGHT_SQUARE_BRACKET)
      {
      PUTCHARS(STR_RIGHT_SQUARE_BRACKET);
      posix_state = POSIX_NOT_BRACKET;
      }

    /* Not the end of the class */

    else
      {
      switch (posix_state)
        {
        case POSIX_CLASS_STARTED:
        if (c <= 127 && islower(c)) break;  /* Remain in started state */
        posix_state = POSIX_CLASS_NOT_STARTED;
        if (c == CHAR_COLON  && plength > 0 &&
            *posix == CHAR_RIGHT_SQUARE_BRACKET)
          {
          PUTCHARS(STR_COLON_RIGHT_SQUARE_BRACKET);
          plength--;
          posix++;
          continue;    /* With next character after :] */
          }
        /* Fall through */

        case POSIX_CLASS_NOT_STARTED:
        if (c == CHAR_LEFT_SQUARE_BRACKET)
          posix_state = POSIX_CLASS_STARTING;
        break;

        case POSIX_CLASS_STARTING:
        if (c == CHAR_COLON) posix_state = POSIX_CLASS_STARTED;
        break;
        }

      if (c == CHAR_BACKSLASH) PUTCHARS(STR_BACKSLASH);
      if (p + clength > endp) return PCRE2_ERROR_NOMEMORY;
      memcpy(p, posix - clength, CU2BYTES(clength));
      p += clength;
      }
    }

  /* Handle a character not within a class. */

  else switch(sc)
    {
    case CHAR_LEFT_SQUARE_BRACKET:
    PUTCHARS(STR_LEFT_SQUARE_BRACKET);

#ifdef NEVER
    /* We could handle special cases [[:<:]] and [[:>:]] (which PCRE does
    support) but they are not part of POSIX 1003.1. */

    if (plength >= 6)
      {
      if (posix[0] == CHAR_LEFT_SQUARE_BRACKET &&
          posix[1] == CHAR_COLON &&
          (posix[2] == CHAR_LESS_THAN_SIGN ||
           posix[2] == CHAR_GREATER_THAN_SIGN) &&
          posix[3] == CHAR_COLON &&
          posix[4] == CHAR_RIGHT_SQUARE_BRACKET &&
          posix[5] == CHAR_RIGHT_SQUARE_BRACKET)
        {
        if (p + 6 > endp) return PCRE2_ERROR_NOMEMORY;
        memcpy(p, posix, CU2BYTES(6));
        p += 6;
        posix += 6;
        plength -= 6;
        continue;  /* With next character */
        }
      }
#endif

    /* Handle start of "normal" character classes */

    posix_state = POSIX_CLASS_NOT_STARTED;

    /* Handle ^ and ] as first characters */

    if (plength > 0)
      {
      if (*posix == CHAR_CIRCUMFLEX_ACCENT)
        {
        posix++;
        plength--;
        PUTCHARS(STR_CIRCUMFLEX_ACCENT);
        }
      if (plength > 0 && *posix == CHAR_RIGHT_SQUARE_BRACKET)
        {
        posix++;
        plength--;
        PUTCHARS(STR_RIGHT_SQUARE_BRACKET);
        }
      }
    break;

    case CHAR_BACKSLASH:
    if (plength <= 0) return PCRE2_ERROR_END_BACKSLASH;
    if (extended) nextisliteral = TRUE; else
      {
      if (*posix < 127 && strchr(posix_meta_escapes, *posix) != NULL)
        {
        if (isdigit(*posix)) PUTCHARS(STR_BACKSLASH);
        if (p + 1 > endp) return PCRE2_ERROR_NOMEMORY;
        lastspecial = *p++ = *posix++;
        plength--;
        }
      else nextisliteral = TRUE;
      }
    break;

    case CHAR_RIGHT_PARENTHESIS:
    if (!extended || bracount == 0) goto ESCAPE_LITERAL;
    bracount--;
    goto COPY_SPECIAL;

    case CHAR_LEFT_PARENTHESIS:
    bracount++;
    /* Fall through */

    case CHAR_QUESTION_MARK:
    case CHAR_PLUS:
    case CHAR_LEFT_CURLY_BRACKET:
    case CHAR_RIGHT_CURLY_BRACKET:
    case CHAR_VERTICAL_LINE:
    if (!extended) goto ESCAPE_LITERAL;
    /* Fall through */

    case CHAR_DOT:
    case CHAR_DOLLAR_SIGN:
    posix_state = POSIX_NOT_BRACKET;
    COPY_SPECIAL:
    lastspecial = c;
    if (p + 1 > endp) return PCRE2_ERROR_NOMEMORY;
    *p++ = c;
    break;

    case CHAR_ASTERISK:
    if (lastspecial != CHAR_ASTERISK)
      {
      if (!extended && (posix_state < POSIX_NOT_BRACKET ||
          lastspecial == CHAR_LEFT_PARENTHESIS))
        goto ESCAPE_LITERAL;
      goto COPY_SPECIAL;
      }
    break;   /* Ignore second and subsequent asterisks */

    case CHAR_CIRCUMFLEX_ACCENT:
    if (extended) goto COPY_SPECIAL;
    if (posix_state == POSIX_START_REGEX ||
        lastspecial == CHAR_LEFT_PARENTHESIS)
      {
      posix_state = POSIX_ANCHORED;
      goto COPY_SPECIAL;
      }
    /* Fall through */

    default:
    if (c < 128 && strchr(pcre2_escaped_literals, c) != NULL)
      {
      ESCAPE_LITERAL:
      PUTCHARS(STR_BACKSLASH);
      }
    lastspecial = 0xff;  /* Indicates nothing special */
    if (p + clength > endp) return PCRE2_ERROR_NOMEMORY;
    memcpy(p, posix - clength, CU2BYTES(clength));
    p += clength;
    posix_state = POSIX_NOT_BRACKET;
    break;
    }
  }

if (posix_state >= POSIX_CLASS_NOT_STARTED)
  return PCRE2_ERROR_MISSING_SQUARE_BRACKET;
convlength += p - pp;        /* Final segment */
*bufflenptr = convlength;
*p++ = 0;
return 0;
}