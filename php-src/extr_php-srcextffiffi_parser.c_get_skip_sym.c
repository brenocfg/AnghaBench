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
 int* YYEND ; 
 int* YYPOS ; 
 int YY_AUTO ; 
 int YY_CHAR ; 
 int YY_CHARACTER ; 
 int YY_COMMENT ; 
 int YY_COMPLEX ; 
 int YY_CONST ; 
 int YY_DECNUMBER ; 
 int YY_DOUBLE ; 
 int YY_ENUM ; 
 int YY_EOF ; 
 int YY_EOL ; 
 int YY_EXTERN ; 
 int YY_FLOAT ; 
 int YY_FLOATNUMBER ; 
 int YY_HEXNUMBER ; 
 int YY_ID ; 
 int YY_INLINE ; 
 int YY_INT ; 
 int YY_LONG ; 
 int YY_OCTNUMBER ; 
 int YY_ONE_LINE_COMMENT ; 
 int YY_REGISTER ; 
 int YY_RESTRICT ; 
 int YY_SHORT ; 
 int YY_SIGNED ; 
 int YY_SIZEOF ; 
 int YY_STATIC ; 
 int YY_STRING ; 
 int YY_STRUCT ; 
 int YY_TYPEDEF ; 
 int YY_UNION ; 
 int YY_UNSIGNED ; 
 int YY_VOID ; 
 int YY_VOLATILE ; 
 int YY_WS ; 
 int YY__ALIGNAS ; 
 int YY__ALIGNOF ; 
 int YY__AND ; 
 int YY__AND_AND ; 
 int YY__ATOMIC ; 
 int YY__BANG ; 
 int YY__BANG_EQUAL ; 
 int YY__BAR ; 
 int YY__BAR_BAR ; 
 int YY__BOOL ; 
 int YY__COLON ; 
 int YY__COMMA ; 
 int YY__COMPLEX ; 
 int YY__EQUAL ; 
 int YY__EQUAL_EQUAL ; 
 int YY__GREATER ; 
 int YY__GREATER_EQUAL ; 
 int YY__GREATER_GREATER ; 
 int YY__LBRACE ; 
 int YY__LBRACK ; 
 int YY__LESS ; 
 int YY__LESS_EQUAL ; 
 int YY__LESS_LESS ; 
 int YY__LPAREN ; 
 int YY__MINUS ; 
 int YY__MINUS_GREATER ; 
 int YY__MINUS_MINUS ; 
 int YY__NORETURN ; 
 int YY__PERCENT ; 
 int YY__PLUS ; 
 int YY__PLUS_PLUS ; 
 int YY__POINT ; 
 int YY__POINT_POINT_POINT ; 
 int YY__QUERY ; 
 int YY__RBRACE ; 
 int YY__RBRACK ; 
 int YY__RPAREN ; 
 int YY__SEMICOLON ; 
 int YY__SLASH ; 
 int YY__STAR ; 
 int YY__TILDE ; 
 int YY__UPARROW ; 
 int YY___ALIGNOF ; 
 int YY___ALIGNOF__ ; 
 int YY___ASM__ ; 
 int YY___ATTRIBUTE ; 
 int YY___ATTRIBUTE__ ; 
 int YY___CDECL ; 
 int YY___COMPLEX ; 
 int YY___COMPLEX__ ; 
 int YY___CONST ; 
 int YY___CONST__ ; 
 int YY___DECLSPEC ; 
 int YY___EXTENSION__ ; 
 int YY___FASTCALL ; 
 int YY___INLINE ; 
 int YY___INLINE__ ; 
 int YY___RESTICT ; 
 int YY___RESTRICT ; 
 int YY___RESTRICT__ ; 
 int YY___STDCALL ; 
 int YY___THISCALL ; 
 int YY___VOLATILE ; 
 int YY___VOLATILE__ ; 
 unsigned char* yy_end ; 
 int /*<<< orphan*/  yy_error (char*) ; 
 int /*<<< orphan*/  yy_line ; 
 unsigned char const* yy_pos ; 
 int* yy_text ; 

__attribute__((used)) static int get_skip_sym(void) {
	int ch;
	int ret;
	int accept = -1;
	const unsigned char *accept_pos;
	const unsigned char *cpos = yy_pos;
	const unsigned char *cend = yy_end;

_yy_state_start:
	yy_text = YYPOS;
	ch = *YYPOS;
	switch (ch) {
		case '_':
			ch = *++YYPOS;
			switch (ch) {
				case '_':
					ch = *++YYPOS;
					switch (ch) {
						case 'e':
							ch = *++YYPOS;
							if (ch != 'x') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 't') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'n') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'i') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'o') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'n') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != '_') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != '_') goto _yy_tunnel_9;
							ret = YY___EXTENSION__;
							goto _yy_state_381;
						case 'i':
							ch = *++YYPOS;
							if (ch != 'n') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'i') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'n') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != '_') {ret = YY___INLINE; goto _yy_tunnel_381;}
							ch = *++YYPOS;
							if (ch != '_') goto _yy_tunnel_9;
							ret = YY___INLINE__;
							goto _yy_state_381;
						case 'c':
							ch = *++YYPOS;
							if (ch == 'd') {
								ch = *++YYPOS;
								if (ch != 'e') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'c') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'l') goto _yy_tunnel_9;
								ret = YY___CDECL;
								goto _yy_state_381;
							} else if (ch == 'o') {
								ch = *++YYPOS;
								if (ch == 'm') {
									ch = *++YYPOS;
									if (ch != 'p') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != 'l') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != 'e') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != 'x') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != '_') {ret = YY___COMPLEX; goto _yy_tunnel_381;}
									ch = *++YYPOS;
									if (ch != '_') goto _yy_tunnel_9;
									ret = YY___COMPLEX__;
									goto _yy_state_381;
								} else if (ch == 'n') {
									ch = *++YYPOS;
									if (ch != 's') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != 't') goto _yy_tunnel_9;
									ch = *++YYPOS;
									if (ch != '_') {ret = YY___CONST; goto _yy_tunnel_381;}
									ch = *++YYPOS;
									if (ch != '_') goto _yy_tunnel_9;
									ret = YY___CONST__;
									goto _yy_state_381;
								} else {
									goto _yy_tunnel_9;
								}
							} else {
								goto _yy_tunnel_9;
							}
						case 's':
							ch = *++YYPOS;
							if (ch != 't') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'd') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'c') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'a') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ret = YY___STDCALL;
							goto _yy_state_381;
						case 'f':
							ch = *++YYPOS;
							if (ch != 'a') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 't') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'c') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'a') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ret = YY___FASTCALL;
							goto _yy_state_381;
						case 't':
							ch = *++YYPOS;
							if (ch != 'h') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'i') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'c') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'a') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ret = YY___THISCALL;
							goto _yy_state_381;
						case 'a':
							ch = *++YYPOS;
							if (ch == 'l') {
								ch = *++YYPOS;
								if (ch != 'i') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'g') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'n') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'o') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'f') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != '_') {ret = YY___ALIGNOF; goto _yy_tunnel_381;}
								ch = *++YYPOS;
								if (ch != '_') goto _yy_tunnel_9;
								ret = YY___ALIGNOF__;
								goto _yy_state_381;
							} else if (ch == 's') {
								ch = *++YYPOS;
								if (ch != 'm') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != '_') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != '_') goto _yy_tunnel_9;
								ret = YY___ASM__;
								goto _yy_state_381;
							} else if (ch == 't') {
								ch = *++YYPOS;
								if (ch != 't') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'r') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'i') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'b') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'u') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 't') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'e') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != '_') {ret = YY___ATTRIBUTE; goto _yy_tunnel_381;}
								ch = *++YYPOS;
								if (ch != '_') goto _yy_tunnel_9;
								ret = YY___ATTRIBUTE__;
								goto _yy_state_381;
							} else {
								goto _yy_tunnel_9;
							}
						case 'd':
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'c') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'p') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'c') goto _yy_tunnel_9;
							ret = YY___DECLSPEC;
							goto _yy_state_381;
						case 'r':
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 't') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch == 'i') {
								ch = *++YYPOS;
								if (ch != 'c') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 't') goto _yy_tunnel_9;
								ret = YY___RESTICT;
								goto _yy_state_381;
							} else if (ch == 'r') {
								ch = *++YYPOS;
								if (ch != 'i') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 'c') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != 't') goto _yy_tunnel_9;
								ch = *++YYPOS;
								if (ch != '_') {ret = YY___RESTRICT; goto _yy_tunnel_381;}
								ch = *++YYPOS;
								if (ch != '_') goto _yy_tunnel_9;
								ret = YY___RESTRICT__;
								goto _yy_state_381;
							} else {
								goto _yy_tunnel_9;
							}
						case 'v':
							ch = *++YYPOS;
							if (ch != 'o') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'a') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 't') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'i') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'l') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != 'e') goto _yy_tunnel_9;
							ch = *++YYPOS;
							if (ch != '_') {ret = YY___VOLATILE; goto _yy_tunnel_381;}
							ch = *++YYPOS;
							if (ch != '_') goto _yy_tunnel_9;
							ret = YY___VOLATILE__;
							goto _yy_state_381;
						default:
							goto _yy_tunnel_9;
					}
				case 'N':
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'r') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 't') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'u') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'r') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'n') goto _yy_tunnel_9;
					ret = YY__NORETURN;
					goto _yy_state_381;
				case 'A':
					ch = *++YYPOS;
					if (ch == 'l') {
						ch = *++YYPOS;
						if (ch != 'i') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch != 'g') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch != 'n') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch == 'a') {
							ch = *++YYPOS;
							if (ch != 's') goto _yy_tunnel_9;
							ret = YY__ALIGNAS;
							goto _yy_state_381;
						} else if (ch == 'o') {
							ch = *++YYPOS;
							if (ch != 'f') goto _yy_tunnel_9;
							ret = YY__ALIGNOF;
							goto _yy_state_381;
						} else {
							goto _yy_tunnel_9;
						}
					} else if (ch == 't') {
						ch = *++YYPOS;
						if (ch != 'o') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch != 'm') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch != 'i') goto _yy_tunnel_9;
						ch = *++YYPOS;
						if (ch != 'c') goto _yy_tunnel_9;
						ret = YY__ATOMIC;
						goto _yy_state_381;
					} else {
						goto _yy_tunnel_9;
					}
				case 'B':
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'l') goto _yy_tunnel_9;
					ret = YY__BOOL;
					goto _yy_state_381;
				case 'C':
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'm') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'p') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'l') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'x') goto _yy_tunnel_9;
					ret = YY__COMPLEX;
					goto _yy_state_381;
				default:
					goto _yy_tunnel_9;
			}
		case 't':
			ch = *++YYPOS;
			if (ch != 'y') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'p') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'e') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'd') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'e') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'f') goto _yy_tunnel_9;
			ret = YY_TYPEDEF;
			goto _yy_state_381;
		case 'e':
			ch = *++YYPOS;
			if (ch == 'x') {
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'e') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'r') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'n') goto _yy_tunnel_9;
				ret = YY_EXTERN;
				goto _yy_state_381;
			} else if (ch == 'n') {
				ch = *++YYPOS;
				if (ch != 'u') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'm') goto _yy_tunnel_9;
				ret = YY_ENUM;
				goto _yy_state_381;
			} else {
				goto _yy_tunnel_9;
			}
		case 's':
			ch = *++YYPOS;
			if (ch == 't') {
				ch = *++YYPOS;
				if (ch == 'a') {
					ch = *++YYPOS;
					if (ch != 't') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'i') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'c') goto _yy_tunnel_9;
					ret = YY_STATIC;
					goto _yy_state_381;
				} else if (ch == 'r') {
					ch = *++YYPOS;
					if (ch != 'u') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'c') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 't') goto _yy_tunnel_9;
					ret = YY_STRUCT;
					goto _yy_state_381;
				} else {
					goto _yy_tunnel_9;
				}
			} else if (ch == 'h') {
				ch = *++YYPOS;
				if (ch != 'o') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'r') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ret = YY_SHORT;
				goto _yy_state_381;
			} else if (ch == 'i') {
				ch = *++YYPOS;
				if (ch == 'g') {
					ch = *++YYPOS;
					if (ch != 'n') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'd') goto _yy_tunnel_9;
					ret = YY_SIGNED;
					goto _yy_state_381;
				} else if (ch == 'z') {
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'f') goto _yy_tunnel_9;
					ret = YY_SIZEOF;
					goto _yy_state_381;
				} else {
					goto _yy_tunnel_9;
				}
			} else {
				goto _yy_tunnel_9;
			}
		case 'a':
			ch = *++YYPOS;
			if (ch != 'u') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 't') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'o') goto _yy_tunnel_9;
			ret = YY_AUTO;
			goto _yy_state_381;
		case 'r':
			ch = *++YYPOS;
			if (ch != 'e') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch == 'g') {
				ch = *++YYPOS;
				if (ch != 'i') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 's') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'e') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'r') goto _yy_tunnel_9;
				ret = YY_REGISTER;
				goto _yy_state_381;
			} else if (ch == 's') {
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'r') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'i') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'c') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ret = YY_RESTRICT;
				goto _yy_state_381;
			} else {
				goto _yy_tunnel_9;
			}
		case 'i':
			ch = *++YYPOS;
			if (ch != 'n') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch == 'l') {
				ch = *++YYPOS;
				if (ch != 'i') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'n') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'e') goto _yy_tunnel_9;
				ret = YY_INLINE;
				goto _yy_state_381;
			} else if (ch == 't') {
				ret = YY_INT;
				goto _yy_state_381;
			} else {
				goto _yy_tunnel_9;
			}
		case '(':
			YYPOS++;
			ret = YY__LPAREN;
			goto _yy_fin;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'b':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			goto _yy_state_9;
		case 'L':
		case 'U':
			ch = *++YYPOS;
			if (ch == '"') {
				goto _yy_state_27;
			} else if (ch == '\'') {
				goto _yy_state_28;
			} else {
				goto _yy_tunnel_9;
			}
		case 'c':
			ch = *++YYPOS;
			if (ch == 'h') {
				ch = *++YYPOS;
				if (ch != 'a') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'r') goto _yy_tunnel_9;
				ret = YY_CHAR;
				goto _yy_state_381;
			} else if (ch == 'o') {
				ch = *++YYPOS;
				if (ch == 'm') {
					ch = *++YYPOS;
					if (ch != 'p') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'l') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'x') goto _yy_tunnel_9;
					ret = YY_COMPLEX;
					goto _yy_state_381;
				} else if (ch == 'n') {
					ch = *++YYPOS;
					if (ch != 's') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 't') goto _yy_tunnel_9;
					ret = YY_CONST;
					goto _yy_state_381;
				} else {
					goto _yy_tunnel_9;
				}
			} else {
				goto _yy_tunnel_9;
			}
		case 'd':
			ch = *++YYPOS;
			if (ch != 'o') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'u') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'b') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'l') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'e') goto _yy_tunnel_9;
			ret = YY_DOUBLE;
			goto _yy_state_381;
		case 'f':
			ch = *++YYPOS;
			if (ch != 'l') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'o') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'a') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 't') goto _yy_tunnel_9;
			ret = YY_FLOAT;
			goto _yy_state_381;
		case 'l':
			ch = *++YYPOS;
			if (ch != 'o') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'n') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch != 'g') goto _yy_tunnel_9;
			ret = YY_LONG;
			goto _yy_state_381;
		case 'u':
			ch = *++YYPOS;
			if (ch == 'n') {
				ch = *++YYPOS;
				if (ch == 'i') {
					ch = *++YYPOS;
					if (ch != 'o') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'n') goto _yy_tunnel_9;
					ret = YY_UNION;
					goto _yy_state_381;
				} else if (ch == 's') {
					ch = *++YYPOS;
					if (ch != 'i') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'g') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'n') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'e') goto _yy_tunnel_9;
					ch = *++YYPOS;
					if (ch != 'd') goto _yy_tunnel_9;
					ret = YY_UNSIGNED;
					goto _yy_state_381;
				} else {
					goto _yy_tunnel_9;
				}
			} else if (ch == '8') {
				ch = *++YYPOS;
				if (ch != '"') goto _yy_tunnel_9;
				goto _yy_state_27;
			} else if (ch == '"') {
				goto _yy_state_27;
			} else if (ch == '\'') {
				goto _yy_state_28;
			} else {
				goto _yy_tunnel_9;
			}
		case 'v':
			ch = *++YYPOS;
			if (ch != 'o') goto _yy_tunnel_9;
			ch = *++YYPOS;
			if (ch == 'i') {
				ch = *++YYPOS;
				if (ch != 'd') goto _yy_tunnel_9;
				ret = YY_VOID;
				goto _yy_state_381;
			} else if (ch == 'l') {
				ch = *++YYPOS;
				if (ch != 'a') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 't') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'i') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'l') goto _yy_tunnel_9;
				ch = *++YYPOS;
				if (ch != 'e') goto _yy_tunnel_9;
				ret = YY_VOLATILE;
				goto _yy_state_381;
			} else {
				goto _yy_tunnel_9;
			}
		case ')':
			YYPOS++;
			ret = YY__RPAREN;
			goto _yy_fin;
		case '[':
			YYPOS++;
			ret = YY__LBRACK;
			goto _yy_fin;
		case ',':
			YYPOS++;
			ret = YY__COMMA;
			goto _yy_fin;
		case ']':
			YYPOS++;
			ret = YY__RBRACK;
			goto _yy_fin;
		case '.':
			ch = *++YYPOS;
			accept = YY__POINT;
			accept_pos = yy_pos;
			if ((ch >= '0' && ch <= '9')) {
				goto _yy_state_73;
			} else if (ch == '.') {
				ch = *++YYPOS;
				if (ch == '.') {
					YYPOS++;
					ret = YY__POINT_POINT_POINT;
					goto _yy_fin;
				} else {
					goto _yy_state_error;
				}
			} else {
				ret = YY__POINT;
				goto _yy_fin;
			}
		case '-':
			ch = *++YYPOS;
			if (ch == '>') {
				YYPOS++;
				ret = YY__MINUS_GREATER;
				goto _yy_fin;
			} else if (ch == '-') {
				YYPOS++;
				ret = YY__MINUS_MINUS;
				goto _yy_fin;
			} else {
				ret = YY__MINUS;
				goto _yy_fin;
			}
		case '+':
			ch = *++YYPOS;
			if (ch == '+') {
				YYPOS++;
				ret = YY__PLUS_PLUS;
				goto _yy_fin;
			} else {
				ret = YY__PLUS;
				goto _yy_fin;
			}
		case '0':
			ch = *++YYPOS;
			if (ch != 'X' && ch != 'x') goto _yy_tunnel_78;
			ch = *++YYPOS;
			if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
				goto _yy_state_156;
			} else {
				goto _yy_state_error;
			}
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			goto _yy_state_26;
		case '"':
			goto _yy_state_27;
		case '\'':
			goto _yy_state_28;
		case '&':
			ch = *++YYPOS;
			if (ch == '&') {
				YYPOS++;
				ret = YY__AND_AND;
				goto _yy_fin;
			} else {
				ret = YY__AND;
				goto _yy_fin;
			}
		case '*':
			YYPOS++;
			ret = YY__STAR;
			goto _yy_fin;
		case '~':
			YYPOS++;
			ret = YY__TILDE;
			goto _yy_fin;
		case '!':
			ch = *++YYPOS;
			if (ch == '=') {
				YYPOS++;
				ret = YY__BANG_EQUAL;
				goto _yy_fin;
			} else {
				ret = YY__BANG;
				goto _yy_fin;
			}
		case '/':
			ch = *++YYPOS;
			accept = YY__SLASH;
			accept_pos = yy_pos;
			if (ch == '*') {
				goto _yy_state_99;
			} else if (ch == '/') {
				goto _yy_state_48;
			} else {
				ret = YY__SLASH;
				goto _yy_fin;
			}
		case '%':
			YYPOS++;
			ret = YY__PERCENT;
			goto _yy_fin;
		case '<':
			ch = *++YYPOS;
			if (ch == '<') {
				YYPOS++;
				ret = YY__LESS_LESS;
				goto _yy_fin;
			} else if (ch == '=') {
				YYPOS++;
				ret = YY__LESS_EQUAL;
				goto _yy_fin;
			} else {
				ret = YY__LESS;
				goto _yy_fin;
			}
		case '>':
			ch = *++YYPOS;
			if (ch == '>') {
				YYPOS++;
				ret = YY__GREATER_GREATER;
				goto _yy_fin;
			} else if (ch == '=') {
				YYPOS++;
				ret = YY__GREATER_EQUAL;
				goto _yy_fin;
			} else {
				ret = YY__GREATER;
				goto _yy_fin;
			}
		case '=':
			ch = *++YYPOS;
			if (ch == '=') {
				YYPOS++;
				ret = YY__EQUAL_EQUAL;
				goto _yy_fin;
			} else {
				ret = YY__EQUAL;
				goto _yy_fin;
			}
		case '^':
			YYPOS++;
			ret = YY__UPARROW;
			goto _yy_fin;
		case '|':
			ch = *++YYPOS;
			if (ch == '|') {
				YYPOS++;
				ret = YY__BAR_BAR;
				goto _yy_fin;
			} else {
				ret = YY__BAR;
				goto _yy_fin;
			}
		case '?':
			YYPOS++;
			ret = YY__QUERY;
			goto _yy_fin;
		case ':':
			YYPOS++;
			ret = YY__COLON;
			goto _yy_fin;
		case '{':
			YYPOS++;
			ret = YY__LBRACE;
			goto _yy_fin;
		case ';':
			YYPOS++;
			ret = YY__SEMICOLON;
			goto _yy_fin;
		case '}':
			YYPOS++;
			ret = YY__RBRACE;
			goto _yy_fin;
		case '\r':
			ch = *++YYPOS;
			if (ch == '\n') {
				yy_line++;
				YYPOS++;
				ret = YY_EOL;
				goto _yy_fin;
			} else {
				ret = YY_EOL;
				goto _yy_fin;
			}
		case '\n':
			yy_line++;
			YYPOS++;
			ret = YY_EOL;
			goto _yy_fin;
		case ' ':
		case '\t':
		case '\f':
		case '\v':
			goto _yy_state_47;
		case '#':
			goto _yy_state_48;
		case '\0':
			if (ch == 0 && YYPOS < YYEND) goto _yy_state_error;
			YYPOS++;
			ret = YY_EOF;
			goto _yy_fin;
		default:
			goto _yy_state_error;
	}
_yy_state_9:
	ch = *++YYPOS;
_yy_tunnel_9:
	if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= 'a' && ch <= 'z')) {
		goto _yy_state_9;
	} else {
		ret = YY_ID;
		goto _yy_fin;
	}
_yy_state_26:
	ch = *++YYPOS;
	accept = YY_DECNUMBER;
	accept_pos = yy_pos;
	switch (ch) {
		case 'U':
		case 'u':
			ch = *++YYPOS;
			if (ch == 'L') {
				ch = *++YYPOS;
				if (ch == 'L') {
					YYPOS++;
					ret = YY_DECNUMBER;
					goto _yy_fin;
				} else {
					ret = YY_DECNUMBER;
					goto _yy_fin;
				}
			} else if (ch == 'l') {
				YYPOS++;
				ret = YY_DECNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_DECNUMBER;
				goto _yy_fin;
			}
		case 'L':
			ch = *++YYPOS;
			accept = YY_DECNUMBER;
			accept_pos = yy_pos;
			if (ch == 'L') {
				goto _yy_state_163;
			} else if (ch == 'U' || ch == 'u') {
				YYPOS++;
				ret = YY_DECNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_DECNUMBER;
				goto _yy_fin;
			}
		case 'l':
			ch = *++YYPOS;
			accept = YY_DECNUMBER;
			accept_pos = yy_pos;
			if (ch == 'U' || ch == 'u') {
				YYPOS++;
				ret = YY_DECNUMBER;
				goto _yy_fin;
			} else if (ch == 'l') {
				goto _yy_state_163;
			} else {
				ret = YY_DECNUMBER;
				goto _yy_fin;
			}
		case 'E':
		case 'e':
			goto _yy_state_85;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			goto _yy_state_26;
		case '.':
			goto _yy_state_73;
		default:
			ret = YY_DECNUMBER;
			goto _yy_fin;
	}
_yy_state_27:
	ch = *++YYPOS;
	if (ch == '\\') {
		ch = *++YYPOS;
		if (YYPOS < YYEND) {
			if (ch == '\n') {
				yy_line++;
			}
			goto _yy_state_27;
		} else {
			goto _yy_state_error;
		}
	} else if (ch == '"') {
		YYPOS++;
		ret = YY_STRING;
		goto _yy_fin;
	} else if (YYPOS < YYEND && (ch <= '!' || (ch >= '#' && ch <= '[') || ch >= ']')) {
		if (ch == '\n') {
			yy_line++;
		}
		goto _yy_state_27;
	} else {
		goto _yy_state_error;
	}
_yy_state_28:
	ch = *++YYPOS;
	if (ch == '\\') {
		ch = *++YYPOS;
		if (YYPOS < YYEND) {
			if (ch == '\n') {
				yy_line++;
			}
			goto _yy_state_28;
		} else {
			goto _yy_state_error;
		}
	} else if (ch == '\'') {
		YYPOS++;
		ret = YY_CHARACTER;
		goto _yy_fin;
	} else if (YYPOS < YYEND && (ch <= '&' || (ch >= '(' && ch <= '[') || ch >= ']')) {
		if (ch == '\n') {
			yy_line++;
		}
		goto _yy_state_28;
	} else {
		goto _yy_state_error;
	}
_yy_state_47:
	ch = *++YYPOS;
	if (ch == '\t' || ch == '\v' || ch == '\f' || ch == ' ') {
		goto _yy_state_47;
	} else {
		ret = YY_WS;
		goto _yy_fin;
	}
_yy_state_48:
	ch = *++YYPOS;
	if (ch == '\r') {
		ch = *++YYPOS;
		if (ch == '\n') {
			yy_line++;
			YYPOS++;
			ret = YY_ONE_LINE_COMMENT;
			goto _yy_fin;
		} else {
			ret = YY_ONE_LINE_COMMENT;
			goto _yy_fin;
		}
	} else if (ch == '\n') {
		yy_line++;
		YYPOS++;
		ret = YY_ONE_LINE_COMMENT;
		goto _yy_fin;
	} else if (YYPOS < YYEND && (ch <= '\t' || ch == '\v' || ch == '\f' || ch >= '\016')) {
		goto _yy_state_48;
	} else {
		goto _yy_state_error;
	}
_yy_state_73:
	ch = *++YYPOS;
	accept = YY_FLOATNUMBER;
	accept_pos = yy_pos;
	if ((ch >= '0' && ch <= '9')) {
		goto _yy_state_73;
	} else if (ch == 'F' || ch == 'L' || ch == 'f' || ch == 'l') {
		YYPOS++;
		ret = YY_FLOATNUMBER;
		goto _yy_fin;
	} else if (ch == 'E' || ch == 'e') {
		goto _yy_state_85;
	} else {
		ret = YY_FLOATNUMBER;
		goto _yy_fin;
	}
_yy_state_78:
	ch = *++YYPOS;
_yy_tunnel_78:
	accept = YY_OCTNUMBER;
	accept_pos = yy_pos;
	switch (ch) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
			goto _yy_state_78;
		case 'U':
		case 'u':
			ch = *++YYPOS;
			if (ch == 'L') {
				ch = *++YYPOS;
				if (ch == 'L') {
					YYPOS++;
					ret = YY_OCTNUMBER;
					goto _yy_fin;
				} else {
					ret = YY_OCTNUMBER;
					goto _yy_fin;
				}
			} else if (ch == 'l') {
				YYPOS++;
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			}
		case 'L':
			ch = *++YYPOS;
			accept = YY_OCTNUMBER;
			accept_pos = yy_pos;
			if (ch == 'L') {
				goto _yy_state_154;
			} else if (ch == 'U' || ch == 'u') {
				YYPOS++;
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			}
		case 'l':
			ch = *++YYPOS;
			accept = YY_OCTNUMBER;
			accept_pos = yy_pos;
			if (ch == 'l') {
				goto _yy_state_154;
			} else if (ch == 'U' || ch == 'u') {
				YYPOS++;
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_OCTNUMBER;
				goto _yy_fin;
			}
		case '8':
		case '9':
			goto _yy_state_83;
		case 'E':
		case 'e':
			goto _yy_state_85;
		case '.':
			goto _yy_state_73;
		default:
			ret = YY_OCTNUMBER;
			goto _yy_fin;
	}
_yy_state_83:
	ch = *++YYPOS;
	if ((ch >= '0' && ch <= '9')) {
		goto _yy_state_83;
	} else if (ch == 'E' || ch == 'e') {
		goto _yy_state_85;
	} else if (ch == '.') {
		goto _yy_state_73;
	} else {
		goto _yy_state_error;
	}
_yy_state_85:
	ch = *++YYPOS;
	if (ch == '+' || ch == '-') {
		ch = *++YYPOS;
		if ((ch >= '0' && ch <= '9')) {
			goto _yy_state_159;
		} else {
			goto _yy_state_error;
		}
	} else if ((ch >= '0' && ch <= '9')) {
		goto _yy_state_159;
	} else {
		goto _yy_state_error;
	}
_yy_state_99:
	ch = *++YYPOS;
_yy_tunnel_99:
	if (ch == '*') {
		ch = *++YYPOS;
		if (ch != '/') goto _yy_tunnel_99;
		YYPOS++;
		ret = YY_COMMENT;
		goto _yy_fin;
	} else if (YYPOS < YYEND && (ch <= ')' || ch >= '+')) {
		if (ch == '\n') {
			yy_line++;
		}
		goto _yy_state_99;
	} else {
		goto _yy_state_error;
	}
_yy_state_154:
	ch = *++YYPOS;
	if (ch == 'U' || ch == 'u') {
		YYPOS++;
		ret = YY_OCTNUMBER;
		goto _yy_fin;
	} else {
		goto _yy_state_error;
	}
_yy_state_156:
	ch = *++YYPOS;
	if (ch == 'U' || ch == 'u') {
		ch = *++YYPOS;
		if (ch == 'L') {
			ch = *++YYPOS;
			if (ch == 'L') {
				YYPOS++;
				ret = YY_HEXNUMBER;
				goto _yy_fin;
			} else {
				ret = YY_HEXNUMBER;
				goto _yy_fin;
			}
		} else if (ch == 'l') {
			YYPOS++;
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		} else {
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		}
	} else if (ch == 'L') {
		ch = *++YYPOS;
		accept = YY_HEXNUMBER;
		accept_pos = yy_pos;
		if (ch == 'L') {
			goto _yy_state_263;
		} else if (ch == 'U' || ch == 'u') {
			YYPOS++;
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		} else {
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		}
	} else if (ch == 'l') {
		ch = *++YYPOS;
		accept = YY_HEXNUMBER;
		accept_pos = yy_pos;
		if (ch == 'U' || ch == 'u') {
			YYPOS++;
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		} else if (ch == 'l') {
			goto _yy_state_263;
		} else {
			ret = YY_HEXNUMBER;
			goto _yy_fin;
		}
	} else if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
		goto _yy_state_156;
	} else {
		ret = YY_HEXNUMBER;
		goto _yy_fin;
	}
_yy_state_159:
	ch = *++YYPOS;
	if ((ch >= '0' && ch <= '9')) {
		goto _yy_state_159;
	} else if (ch == 'F' || ch == 'L' || ch == 'f' || ch == 'l') {
		YYPOS++;
		ret = YY_FLOATNUMBER;
		goto _yy_fin;
	} else {
		ret = YY_FLOATNUMBER;
		goto _yy_fin;
	}
_yy_state_163:
	ch = *++YYPOS;
	if (ch == 'U' || ch == 'u') {
		YYPOS++;
		ret = YY_DECNUMBER;
		goto _yy_fin;
	} else {
		goto _yy_state_error;
	}
_yy_state_263:
	ch = *++YYPOS;
	if (ch == 'U' || ch == 'u') {
		YYPOS++;
		ret = YY_HEXNUMBER;
		goto _yy_fin;
	} else {
		goto _yy_state_error;
	}
_yy_state_381:
	ch = *++YYPOS;
_yy_tunnel_381:
	if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= 'a' && ch <= 'z')) {
		goto _yy_state_9;
	} else {
		goto _yy_fin;
	}
_yy_state_error:
	if (accept >= 0) {
		yy_pos = accept_pos;
		return accept;
	}
	if (YYPOS >= YYEND) {
		yy_error("unexpected <EOF>");
	} else if (YYPOS == yy_text) {
		yy_error("unexpected character 'escape_char(ch)'");
	} else {
		yy_error("unexpected sequence 'escape_string(yy_text, 1 + YYPOS - yy_text))'");
	}
	YYPOS++;
	goto _yy_state_start;
_yy_fin:
	yy_pos = YYPOS;
	return ret;
}