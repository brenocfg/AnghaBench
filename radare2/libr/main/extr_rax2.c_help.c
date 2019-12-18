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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int help() {
	printf (
		"  =[base]                      ;  rax2 =10 0x46 -> output in base 10\n"
		"  int     ->  hex              ;  rax2 10\n"
		"  hex     ->  int              ;  rax2 0xa\n"
		"  -int    ->  hex              ;  rax2 -77\n"
		"  -hex    ->  int              ;  rax2 0xffffffb3\n"
		"  int     ->  bin              ;  rax2 b30\n"
		"  int     ->  ternary          ;  rax2 t42\n"
		"  bin     ->  int              ;  rax2 1010d\n"
		"  ternary ->  int              ;  rax2 1010dt\n"
		"  float   ->  hex              ;  rax2 3.33f\n"
		"  hex     ->  float            ;  rax2 Fx40551ed8\n"
		"  oct     ->  hex              ;  rax2 35o\n"
		"  hex     ->  oct              ;  rax2 Ox12 (O is a letter)\n"
		"  bin     ->  hex              ;  rax2 1100011b\n"
		"  hex     ->  bin              ;  rax2 Bx63\n"
		"  ternary ->  hex              ;  rax2 212t\n"
		"  hex     ->  ternary          ;  rax2 Tx23\n"
		"  raw     ->  hex              ;  rax2 -S < /binfile\n"
		"  hex     ->  raw              ;  rax2 -s 414141\n"
		"  -l                           ;  append newline to output (for -E/-D/-r/..\n"
		"  -a      show ascii table     ;  rax2 -a\n"
		"  -b      bin -> str           ;  rax2 -b 01000101 01110110\n"
		"  -B      str -> bin           ;  rax2 -B hello\n"
		"  -d      force integer        ;  rax2 -d 3 -> 3 instead of 0x3\n"
		"  -e      swap endianness      ;  rax2 -e 0x33\n"
		"  -D      base64 decode        ;\n"
		"  -E      base64 encode        ;\n"
		"  -f      floating point       ;  rax2 -f 6.3+2.1\n"
		"  -F      stdin slurp code hex ;  rax2 -F < shellcode.[c/py/js]\n"
		"  -h      help                 ;  rax2 -h\n"
		"  -i      dump as C byte array ;  rax2 -i < bytes\n"
		"  -k      keep base            ;  rax2 -k 33+3 -> 36\n"
		"  -K      randomart            ;  rax2 -K 0x34 1020304050\n"
		"  -L      bin -> hex(bignum)   ;  rax2 -L 111111111 # 0x1ff\n"
		"  -n      binary number        ;  rax2 -n 0x1234 # 34120000\n"
		"  -o      octalstr -> raw      ;  rax2 -o \\162 \\62 # r2\n"
		"  -N      binary number        ;  rax2 -N 0x1234 # \\x34\\x12\\x00\\x00\n"
		"  -r      r2 style output      ;  rax2 -r 0x1234\n"
		"  -s      hexstr -> raw        ;  rax2 -s 43 4a 50\n"
		"  -S      raw -> hexstr        ;  rax2 -S < /bin/ls > ls.hex\n"
		"  -t      tstamp -> str        ;  rax2 -t 1234567890\n"
		"  -x      hash string          ;  rax2 -x linux osx\n"
		"  -u      units                ;  rax2 -u 389289238 # 317.0M\n"
		"  -w      signed word          ;  rax2 -w 16 0xffff\n"
		"  -v      version              ;  rax2 -v\n");
	return true;
}