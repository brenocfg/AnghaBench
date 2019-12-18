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
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_CANGLE ; 
 int /*<<< orphan*/  TOKEN_CBRACE ; 
 int /*<<< orphan*/  TOKEN_CBRACKET ; 
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_CPAREN ; 
 int /*<<< orphan*/  TOKEN_OANGLE ; 
 int /*<<< orphan*/  TOKEN_OBRACE ; 
 int /*<<< orphan*/  TOKEN_OBRACKET ; 
 int /*<<< orphan*/  TOKEN_OPAREN ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 

__attribute__((used)) static WORD get_operator_token(char c)
{
  switch(c)
  {
    case '{':
      return TOKEN_OBRACE;
    case '}':
      return TOKEN_CBRACE;
    case '[':
      return TOKEN_OBRACKET;
    case ']':
      return TOKEN_CBRACKET;
    case '(':
      return TOKEN_OPAREN;
    case ')':
      return TOKEN_CPAREN;
    case '<':
      return TOKEN_OANGLE;
    case '>':
      return TOKEN_CANGLE;
    case ',':
      return TOKEN_COMMA;
    case ';':
      return TOKEN_SEMICOLON;
  }
  return 0;
}