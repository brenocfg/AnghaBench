#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* insts; int len; int sub; } ;
typedef  TYPE_1__ ByteProg ;

/* Variables and functions */
 int Any ; 
 int Bol ; 
 int Char ; 
 int Class ; 
 int ClassNot ; 
 int /*<<< orphan*/  EMIT (int,char const) ; 
 int Eol ; 
 int /*<<< orphan*/  INSERT_CODE (int,int,int) ; 
 int Jmp ; 
 int NamedClass ; 
 int PC ; 
 int REL (int,int) ; 
 int RSplit ; 
 int Save ; 
 int Split ; 

__attribute__((used)) static const char *_compilecode(const char *re, ByteProg *prog, int sizecode)
{
    char *code = sizecode ? NULL : prog->insts;
    int start = PC;
    int term = PC;
    int alt_label = 0;

    for (; *re && *re != ')'; re++) {
        switch (*re) {
        case '\\':
            re++;
            if (!*re) return NULL; // Trailing backslash
            if ((*re | 0x20) == 'd' || (*re | 0x20) == 's' || (*re | 0x20) == 'w') {
                term = PC;
                EMIT(PC++, NamedClass);
                EMIT(PC++, *re);
                prog->len++;
                break;
            }
        default:
            term = PC;
            EMIT(PC++, Char);
            EMIT(PC++, *re);
            prog->len++;
            break;
        case '.':
            term = PC;
            EMIT(PC++, Any);
            prog->len++;
            break;
        case '[': {
            int cnt;
            term = PC;
            re++;
            if (*re == '^') {
                EMIT(PC++, ClassNot);
                re++;
            } else {
                EMIT(PC++, Class);
            }
            PC++; // Skip # of pair byte
            prog->len++;
            for (cnt = 0; *re != ']'; re++, cnt++) {
                if (*re == '\\') {
                    ++re;
                }
                if (!*re) return NULL;
                EMIT(PC++, *re);
                if (re[1] == '-' && re[2] != ']') {
                    re += 2;
                }
                EMIT(PC++, *re);
            }
            EMIT(term + 1, cnt);
            break;
        }
        case '(': {
            term = PC;
            int sub = 0;
            int capture = re[1] != '?' || re[2] != ':';

            if (capture) {
                sub = ++prog->sub;
                EMIT(PC++, Save);
                EMIT(PC++, 2 * sub);
                prog->len++;
            } else {
                    re += 2;
            }

            re = _compilecode(re + 1, prog, sizecode);
            if (re == NULL || *re != ')') return NULL; // error, or no matching paren

            if (capture) {
                EMIT(PC++, Save);
                EMIT(PC++, 2 * sub + 1);
                prog->len++;
            }

            break;
        }
        case '?':
            if (PC == term) return NULL; // nothing to repeat
            INSERT_CODE(term, 2, PC);
            if (re[1] == '?') {
                EMIT(term, RSplit);
                re++;
            } else {
                EMIT(term, Split);
            }
            EMIT(term + 1, REL(term, PC));
            prog->len++;
            term = PC;
            break;
        case '*':
            if (PC == term) return NULL; // nothing to repeat
            INSERT_CODE(term, 2, PC);
            EMIT(PC, Jmp);
            EMIT(PC + 1, REL(PC, term));
            PC += 2;
            if (re[1] == '?') {
                EMIT(term, RSplit);
                re++;
            } else {
                EMIT(term, Split);
            }
            EMIT(term + 1, REL(term, PC));
            prog->len += 2;
            term = PC;
            break;
        case '+':
            if (PC == term) return NULL; // nothing to repeat
            if (re[1] == '?') {
                EMIT(PC, Split);
                re++;
            } else {
                EMIT(PC, RSplit);
            }
            EMIT(PC + 1, REL(PC, term));
            PC += 2;
            prog->len++;
            term = PC;
            break;
        case '|':
            if (alt_label) {
                EMIT(alt_label, REL(alt_label, PC) + 1);
            }
            INSERT_CODE(start, 2, PC);
            EMIT(PC++, Jmp);
            alt_label = PC++;
            EMIT(start, Split);
            EMIT(start + 1, REL(start, PC));
            prog->len += 2;
            term = PC;
            break;
        case '^':
            EMIT(PC++, Bol);
            prog->len++;
            term = PC;
            break;
        case '$':
            EMIT(PC++, Eol);
            prog->len++;
            term = PC;
            break;
        }
    }

    if (alt_label) {
        EMIT(alt_label, REL(alt_label, PC) + 1);
    }
    return re;
}