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
typedef  int pcre_uchar ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GET (int const*,int) ; 
 int /*<<< orphan*/  GET_EXTRALEN (int const) ; 
 int /*<<< orphan*/  HAS_EXTRALEN (int const) ; 
 int /*<<< orphan*/  IMM2_SIZE ; 
#define  OP_CHAR 200 
#define  OP_CHARI 199 
 int OP_END ; 
#define  OP_EXACT 198 
#define  OP_EXACTI 197 
#define  OP_MARK 196 
#define  OP_MINPLUS 195 
#define  OP_MINPLUSI 194 
#define  OP_MINQUERY 193 
#define  OP_MINQUERYI 192 
#define  OP_MINSTAR 191 
#define  OP_MINSTARI 190 
#define  OP_MINUPTO 189 
#define  OP_MINUPTOI 188 
#define  OP_NOT 187 
#define  OP_NOTEXACT 186 
#define  OP_NOTEXACTI 185 
#define  OP_NOTI 184 
#define  OP_NOTMINPLUS 183 
#define  OP_NOTMINPLUSI 182 
#define  OP_NOTMINQUERY 181 
#define  OP_NOTMINQUERYI 180 
#define  OP_NOTMINSTAR 179 
#define  OP_NOTMINSTARI 178 
#define  OP_NOTMINUPTO 177 
#define  OP_NOTMINUPTOI 176 
#define  OP_NOTPLUS 175 
#define  OP_NOTPLUSI 174 
#define  OP_NOTPOSPLUS 173 
#define  OP_NOTPOSPLUSI 172 
#define  OP_NOTPOSQUERY 171 
#define  OP_NOTPOSQUERYI 170 
#define  OP_NOTPOSSTAR 169 
#define  OP_NOTPOSSTARI 168 
#define  OP_NOTPOSUPTO 167 
#define  OP_NOTPOSUPTOI 166 
 int const OP_NOTPROP ; 
#define  OP_NOTQUERY 165 
#define  OP_NOTQUERYI 164 
#define  OP_NOTSTAR 163 
#define  OP_NOTSTARI 162 
#define  OP_NOTUPTO 161 
#define  OP_NOTUPTOI 160 
#define  OP_PLUS 159 
#define  OP_PLUSI 158 
#define  OP_POSPLUS 157 
#define  OP_POSPLUSI 156 
#define  OP_POSQUERY 155 
#define  OP_POSQUERYI 154 
#define  OP_POSSTAR 153 
#define  OP_POSSTARI 152 
#define  OP_POSUPTO 151 
#define  OP_POSUPTOI 150 
 int const OP_PROP ; 
#define  OP_PRUNE_ARG 149 
#define  OP_QUERY 148 
#define  OP_QUERYI 147 
 int OP_RECURSE ; 
#define  OP_SKIP_ARG 146 
#define  OP_STAR 145 
#define  OP_STARI 144 
#define  OP_THEN_ARG 143 
#define  OP_TYPEEXACT 142 
#define  OP_TYPEMINPLUS 141 
#define  OP_TYPEMINQUERY 140 
#define  OP_TYPEMINSTAR 139 
#define  OP_TYPEMINUPTO 138 
#define  OP_TYPEPLUS 137 
#define  OP_TYPEPOSPLUS 136 
#define  OP_TYPEPOSQUERY 135 
#define  OP_TYPEPOSSTAR 134 
#define  OP_TYPEPOSUPTO 133 
#define  OP_TYPEQUERY 132 
#define  OP_TYPESTAR 131 
#define  OP_TYPEUPTO 130 
#define  OP_UPTO 129 
#define  OP_UPTOI 128 
 int OP_XCLASS ; 
 int /*<<< orphan*/  OP_lengths ; 
 int /*<<< orphan*/ * PRIV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const pcre_uchar *
find_recurse(const pcre_uchar *code, BOOL utf)
{
for (;;)
  {
  register pcre_uchar c = *code;
  if (c == OP_END) return NULL;
  if (c == OP_RECURSE) return code;

  /* XCLASS is used for classes that cannot be represented just by a bit
  map. This includes negated single high-valued characters. The length in
  the table is zero; the actual length is stored in the compiled code. */

  if (c == OP_XCLASS) code += GET(code, 1);

  /* Otherwise, we can get the item's length from the table, except that for
  repeated character types, we have to test for \p and \P, which have an extra
  two bytes of parameters, and for MARK/PRUNE/SKIP/THEN with an argument, we
  must add in its length. */

  else
    {
    switch(c)
      {
      case OP_TYPESTAR:
      case OP_TYPEMINSTAR:
      case OP_TYPEPLUS:
      case OP_TYPEMINPLUS:
      case OP_TYPEQUERY:
      case OP_TYPEMINQUERY:
      case OP_TYPEPOSSTAR:
      case OP_TYPEPOSPLUS:
      case OP_TYPEPOSQUERY:
      if (code[1] == OP_PROP || code[1] == OP_NOTPROP) code += 2;
      break;

      case OP_TYPEPOSUPTO:
      case OP_TYPEUPTO:
      case OP_TYPEMINUPTO:
      case OP_TYPEEXACT:
      if (code[1 + IMM2_SIZE] == OP_PROP || code[1 + IMM2_SIZE] == OP_NOTPROP)
        code += 2;
      break;

      case OP_MARK:
      case OP_PRUNE_ARG:
      case OP_SKIP_ARG:
      case OP_THEN_ARG:
      code += code[1];
      break;
      }

    /* Add in the fixed length from the table */

    code += PRIV(OP_lengths)[c];

    /* In UTF-8 mode, opcodes that are followed by a character may be followed
    by a multi-byte character. The length in the table is a minimum, so we have
    to arrange to skip the extra bytes. */

#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (utf) switch(c)
      {
      case OP_CHAR:
      case OP_CHARI:
      case OP_NOT:
      case OP_NOTI:
      case OP_EXACT:
      case OP_EXACTI:
      case OP_NOTEXACT:
      case OP_NOTEXACTI:
      case OP_UPTO:
      case OP_UPTOI:
      case OP_NOTUPTO:
      case OP_NOTUPTOI:
      case OP_MINUPTO:
      case OP_MINUPTOI:
      case OP_NOTMINUPTO:
      case OP_NOTMINUPTOI:
      case OP_POSUPTO:
      case OP_POSUPTOI:
      case OP_NOTPOSUPTO:
      case OP_NOTPOSUPTOI:
      case OP_STAR:
      case OP_STARI:
      case OP_NOTSTAR:
      case OP_NOTSTARI:
      case OP_MINSTAR:
      case OP_MINSTARI:
      case OP_NOTMINSTAR:
      case OP_NOTMINSTARI:
      case OP_POSSTAR:
      case OP_POSSTARI:
      case OP_NOTPOSSTAR:
      case OP_NOTPOSSTARI:
      case OP_PLUS:
      case OP_PLUSI:
      case OP_NOTPLUS:
      case OP_NOTPLUSI:
      case OP_MINPLUS:
      case OP_MINPLUSI:
      case OP_NOTMINPLUS:
      case OP_NOTMINPLUSI:
      case OP_POSPLUS:
      case OP_POSPLUSI:
      case OP_NOTPOSPLUS:
      case OP_NOTPOSPLUSI:
      case OP_QUERY:
      case OP_QUERYI:
      case OP_NOTQUERY:
      case OP_NOTQUERYI:
      case OP_MINQUERY:
      case OP_MINQUERYI:
      case OP_NOTMINQUERY:
      case OP_NOTMINQUERYI:
      case OP_POSQUERY:
      case OP_POSQUERYI:
      case OP_NOTPOSQUERY:
      case OP_NOTPOSQUERYI:
      if (HAS_EXTRALEN(code[-1])) code += GET_EXTRALEN(code[-1]);
      break;
      }
#else
    (void)(utf);  /* Keep compiler happy by referencing function argument */
#endif
    }
  }
}