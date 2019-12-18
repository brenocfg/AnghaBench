#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unexpected_end ;
struct mrb_parser_state {scalar_t__ nerr; int lstate; TYPE_1__* error_buffer; scalar_t__ lex_strterm; int /*<<< orphan*/ * parsing_heredoc; } ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_2__ {char* message; } ;

/* Variables and functions */
#define  EXPR_ARG 139 
#define  EXPR_BEG 138 
#define  EXPR_CLASS 137 
#define  EXPR_CMDARG 136 
#define  EXPR_DOT 135 
#define  EXPR_END 134 
#define  EXPR_ENDARG 133 
#define  EXPR_ENDFN 132 
#define  EXPR_FNAME 131 
#define  EXPR_MAX_STATE 130 
#define  EXPR_MID 129 
#define  EXPR_VALUE 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static mrb_bool
is_code_block_open(struct mrb_parser_state *parser)
{
  mrb_bool code_block_open = FALSE;

  /* check for heredoc */
  if (parser->parsing_heredoc != NULL) return TRUE;

  /* check for unterminated string */
  if (parser->lex_strterm) return TRUE;

  /* check if parser error are available */
  if (0 < parser->nerr) {
    const char unexpected_end[] = "syntax error, unexpected $end";
    const char *message = parser->error_buffer[0].message;

    /* a parser error occur, we have to check if */
    /* we need to read one more line or if there is */
    /* a different issue which we have to show to */
    /* the user */

    if (strncmp(message, unexpected_end, sizeof(unexpected_end) - 1) == 0) {
      code_block_open = TRUE;
    }
    else if (strcmp(message, "syntax error, unexpected keyword_end") == 0) {
      code_block_open = FALSE;
    }
    else if (strcmp(message, "syntax error, unexpected tREGEXP_BEG") == 0) {
      code_block_open = FALSE;
    }
    return code_block_open;
  }

  switch (parser->lstate) {

  /* all states which need more code */

  case EXPR_BEG:
    /* beginning of a statement, */
    /* that means previous line ended */
    code_block_open = FALSE;
    break;
  case EXPR_DOT:
    /* a message dot was the last token, */
    /* there has to come more */
    code_block_open = TRUE;
    break;
  case EXPR_CLASS:
    /* a class keyword is not enough! */
    /* we need also a name of the class */
    code_block_open = TRUE;
    break;
  case EXPR_FNAME:
    /* a method name is necessary */
    code_block_open = TRUE;
    break;
  case EXPR_VALUE:
    /* if, elsif, etc. without condition */
    code_block_open = TRUE;
    break;

  /* now all the states which are closed */

  case EXPR_ARG:
    /* an argument is the last token */
    code_block_open = FALSE;
    break;

  /* all states which are unsure */

  case EXPR_CMDARG:
    break;
  case EXPR_END:
    /* an expression was ended */
    break;
  case EXPR_ENDARG:
    /* closing parenthese */
    break;
  case EXPR_ENDFN:
    /* definition end */
    break;
  case EXPR_MID:
    /* jump keyword like break, return, ... */
    break;
  case EXPR_MAX_STATE:
    /* don't know what to do with this token */
    break;
  default:
    /* this state is unexpected! */
    break;
  }

  return code_block_open;
}