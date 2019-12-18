#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_20__ {int /*<<< orphan*/ * ts; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
#define  EOZ 128 
 int /*<<< orphan*/  FIRST_RESERVED ; 
 int NUM_RESERVED ; 
 int TK_CONCAT ; 
 int TK_DOTS ; 
 int TK_EOS ; 
 int TK_EQ ; 
 int TK_GE ; 
 int TK_LE ; 
 int TK_NAME ; 
 int TK_NE ; 
 int TK_NUMBER ; 
 int TK_STRING ; 
 int /*<<< orphan*/  check_next (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  currIsNewline (TYPE_2__*) ; 
 int /*<<< orphan*/  inclinenumber (TYPE_2__*) ; 
 int /*<<< orphan*/  isalnum (char) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  luaX_lexerror (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * luaX_newstring (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaX_tokens ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_bufflen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_resetbuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  next (TYPE_2__*) ; 
 int /*<<< orphan*/  read_long_string (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  read_numeral (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  read_string (TYPE_2__*,char,TYPE_1__*) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 
 int skip_sep (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int llex (LexState *ls, SemInfo *seminfo) {
  luaZ_resetbuffer(ls->buff);
  for (;;) {
    switch (ls->current) {
      case '\n':
      case '\r': {
        inclinenumber(ls);
        continue;
      }
      case '-': {
        next(ls);
        if (ls->current != '-') return '-';
        /* else is a comment */
        next(ls);
        if (ls->current == '[') {
          int sep = skip_sep(ls);
          luaZ_resetbuffer(ls->buff);  /* `skip_sep' may dirty the buffer */
          if (sep >= 0) {
            read_long_string(ls, NULL, sep);  /* long comment */
            luaZ_resetbuffer(ls->buff);
            continue;
          }
        }
        /* else short comment */
        while (!currIsNewline(ls) && ls->current != EOZ)
          next(ls);
        continue;
      }
      case '[': {
        int sep = skip_sep(ls);
        if (sep >= 0) {
          read_long_string(ls, seminfo, sep);
          return TK_STRING;
        }
        else if (sep == -1) return '[';
        else luaX_lexerror(ls, "invalid long string delimiter", TK_STRING);
      }
      case '=': {
        next(ls);
        if (ls->current != '=') return '=';
        else { next(ls); return TK_EQ; }
      }
      case '<': {
        next(ls);
        if (ls->current != '=') return '<';
        else { next(ls); return TK_LE; }
      }
      case '>': {
        next(ls);
        if (ls->current != '=') return '>';
        else { next(ls); return TK_GE; }
      }
      case '~': {
        next(ls);
        if (ls->current != '=') return '~';
        else { next(ls); return TK_NE; }
      }
      case '"':
      case '\'': {
        read_string(ls, ls->current, seminfo);
        return TK_STRING;
      }
      case '.': {
        save_and_next(ls);
        if (check_next(ls, ".")) {
          if (check_next(ls, "."))
            return TK_DOTS;   /* ... */
          else return TK_CONCAT;   /* .. */
        }
        else if (!isdigit(ls->current)) return '.';
        else {
          read_numeral(ls, seminfo);
          return TK_NUMBER;
        }
      }
      case EOZ: {
        return TK_EOS;
      }
      default: {
        if (isspace(ls->current)) {
          lua_assert(!currIsNewline(ls));
          next(ls);
          continue;
        }
        else if (isdigit(ls->current)) {
          read_numeral(ls, seminfo);
          return TK_NUMBER;
        }
        else if (isalpha(ls->current) || ls->current == '_') {
          /* identifier or reserved word */
          TString *ts;
          int i;
          do {
            save_and_next(ls);
          } while (isalnum(ls->current) || ls->current == '_');
          /* look for reserved word */
          save(ls, '\0');
          for (i = 0; i < NUM_RESERVED; i++)
            if (!strcmp(luaX_tokens[i], luaZ_buffer(ls->buff)))
              return i + FIRST_RESERVED;
          ts = luaX_newstring(ls, luaZ_buffer(ls->buff),
                                  luaZ_bufflen(ls->buff) - 1);
          seminfo->ts = ts;
          return TK_NAME;
        }
        else {
          int c = ls->current;
          next(ls);
          return c;  /* single-char tokens (+ - / ...) */
        }
      }
    }
  }
}