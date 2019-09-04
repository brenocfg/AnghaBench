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
struct TYPE_3__ {char* insts; int bytelen; char len; } ;
typedef  TYPE_1__ ByteProg ;

/* Variables and functions */
#define  Any 139 
#define  Bol 138 
#define  Char 137 
#define  Class 136 
#define  ClassNot 135 
#define  Eol 134 
#define  Jmp 133 
#define  Match 132 
#define  NamedClass 131 
#define  RSplit 130 
#define  Save 129 
#define  Split 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void re1_5_dumpcode(ByteProg *prog)
{
    int pc = 0;
    char *code = prog->insts;
    while (pc < prog->bytelen) {
                printf("%2d: ", pc);
                switch(code[pc++]) {
                default:
                        assert(0);
//                        re1_5_fatal("printprog");
                case Split:
                        printf("split %d (%d)\n", pc + (signed char)code[pc] + 1, (signed char)code[pc]);
                        pc++;
                        break;
                case RSplit:
                        printf("rsplit %d (%d)\n", pc + (signed char)code[pc] + 1, (signed char)code[pc]);
                        pc++;
                        break;
                case Jmp:
                        printf("jmp %d (%d)\n", pc + (signed char)code[pc] + 1, (signed char)code[pc]);
                        pc++;
                        break;
                case Char:
                        printf("char %c\n", code[pc++]);
                        break;
                case Any:
                        printf("any\n");
                        break;
                case Class:
                case ClassNot: {
                        int num = code[pc];
                        printf("class%s %d", (code[pc - 1] == ClassNot ? "not" : ""), num);
                        pc++;
                        while (num--) {
                            printf(" 0x%02x-0x%02x", code[pc], code[pc + 1]);
                            pc += 2;
                        }
                        printf("\n");
                        break;
                }
                case NamedClass:
                        printf("namedclass %c\n", code[pc++]);
                        break;
                case Match:
                        printf("match\n");
                        break;
                case Save:
                        printf("save %d\n", (unsigned char)code[pc++]);
                        break;
                case Bol:
                        printf("assert bol\n");
                        break;
                case Eol:
                        printf("assert eol\n");
                        break;
                }
    }
    printf("Bytes: %d, insts: %d\n", prog->bytelen, prog->len);
}