#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int pcre_uint32 ;
typedef  int pcre_uchar ;
struct TYPE_4__ {int /*<<< orphan*/  fcc; } ;
typedef  TYPE_1__ compile_data ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int GET (int*,int) ; 
 int /*<<< orphan*/  GET_EXTRALEN (int) ; 
 int /*<<< orphan*/  HAS_EXTRALEN (int) ; 
 int /*<<< orphan*/  IMM2_SIZE ; 
#define  OP_CHAR 210 
#define  OP_CHARI 209 
 int OP_CLASS ; 
#define  OP_CRMINPLUS 208 
#define  OP_CRMINQUERY 207 
#define  OP_CRMINRANGE 206 
#define  OP_CRMINSTAR 205 
#define  OP_CRPLUS 204 
 int OP_CRPOSPLUS ; 
 int OP_CRPOSQUERY ; 
 int OP_CRPOSRANGE ; 
 int OP_CRPOSSTAR ; 
#define  OP_CRQUERY 203 
#define  OP_CRRANGE 202 
#define  OP_CRSTAR 201 
#define  OP_END 200 
#define  OP_EXACT 199 
#define  OP_EXACTI 198 
#define  OP_MARK 197 
#define  OP_MINPLUS 196 
#define  OP_MINPLUSI 195 
#define  OP_MINQUERY 194 
#define  OP_MINQUERYI 193 
#define  OP_MINSTAR 192 
#define  OP_MINSTARI 191 
#define  OP_MINUPTO 190 
#define  OP_MINUPTOI 189 
 int OP_NCLASS ; 
#define  OP_NOT 188 
#define  OP_NOTEXACT 187 
#define  OP_NOTEXACTI 186 
#define  OP_NOTI 185 
#define  OP_NOTMINPLUS 184 
#define  OP_NOTMINPLUSI 183 
#define  OP_NOTMINQUERY 182 
#define  OP_NOTMINQUERYI 181 
#define  OP_NOTMINSTAR 180 
#define  OP_NOTMINSTARI 179 
#define  OP_NOTMINUPTO 178 
#define  OP_NOTMINUPTOI 177 
#define  OP_NOTPLUS 176 
#define  OP_NOTPLUSI 175 
#define  OP_NOTPOSPLUS 174 
#define  OP_NOTPOSPLUSI 173 
#define  OP_NOTPOSQUERY 172 
#define  OP_NOTPOSQUERYI 171 
#define  OP_NOTPOSSTAR 170 
#define  OP_NOTPOSSTARI 169 
#define  OP_NOTPOSUPTO 168 
#define  OP_NOTPOSUPTOI 167 
 int OP_NOTPROP ; 
#define  OP_NOTQUERY 166 
#define  OP_NOTQUERYI 165 
#define  OP_NOTSTAR 164 
#define  OP_NOTSTARI 163 
#define  OP_NOTUPTO 162 
#define  OP_NOTUPTOI 161 
#define  OP_PLUS 160 
#define  OP_PLUSI 159 
#define  OP_POSPLUS 158 
#define  OP_POSPLUSI 157 
#define  OP_POSQUERY 156 
#define  OP_POSQUERYI 155 
#define  OP_POSSTAR 154 
#define  OP_POSSTARI 153 
#define  OP_POSUPTO 152 
#define  OP_POSUPTOI 151 
 int OP_PROP ; 
#define  OP_PRUNE_ARG 150 
#define  OP_QUERY 149 
#define  OP_QUERYI 148 
#define  OP_SKIP_ARG 147 
#define  OP_STAR 146 
#define  OP_STARI 145 
 int OP_TABLE_LENGTH ; 
#define  OP_THEN_ARG 144 
#define  OP_TYPEEXACT 143 
#define  OP_TYPEMINPLUS 142 
#define  OP_TYPEMINQUERY 141 
#define  OP_TYPEMINSTAR 140 
#define  OP_TYPEMINUPTO 139 
#define  OP_TYPEPLUS 138 
#define  OP_TYPEPOSPLUS 137 
#define  OP_TYPEPOSQUERY 136 
#define  OP_TYPEPOSSTAR 135 
#define  OP_TYPEPOSUPTO 134 
#define  OP_TYPEQUERY 133 
#define  OP_TYPESTAR 132 
#define  OP_TYPEUPTO 131 
#define  OP_UPTO 130 
#define  OP_UPTOI 129 
#define  OP_XCLASS 128 
 int /*<<< orphan*/  OP_lengths ; 
 int /*<<< orphan*/ * PRIV (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_opcodes (int const*,int /*<<< orphan*/ ,TYPE_1__ const*,int*,int const*,int*) ; 
 int* get_chr_property_list (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int get_repeat_base (int) ; 

__attribute__((used)) static void
auto_possessify(pcre_uchar *code, BOOL utf, const compile_data *cd)
{
register pcre_uchar c;
const pcre_uchar *end;
pcre_uchar *repeat_opcode;
pcre_uint32 list[8];
int rec_limit;

for (;;)
  {
  c = *code;

  /* When a pattern with bad UTF-8 encoding is compiled with NO_UTF_CHECK,
  it may compile without complaining, but may get into a loop here if the code
  pointer points to a bad value. This is, of course a documentated possibility,
  when NO_UTF_CHECK is set, so it isn't a bug, but we can detect this case and
  just give up on this optimization. */

  if (c >= OP_TABLE_LENGTH) return;

  if (c >= OP_STAR && c <= OP_TYPEPOSUPTO)
    {
    c -= get_repeat_base(c) - OP_STAR;
    end = (c <= OP_MINUPTO) ?
      get_chr_property_list(code, utf, cd->fcc, list) : NULL;
    list[1] = c == OP_STAR || c == OP_PLUS || c == OP_QUERY || c == OP_UPTO;

    rec_limit = 1000;
    if (end != NULL && compare_opcodes(end, utf, cd, list, end, &rec_limit))
      {
      switch(c)
        {
        case OP_STAR:
        *code += OP_POSSTAR - OP_STAR;
        break;

        case OP_MINSTAR:
        *code += OP_POSSTAR - OP_MINSTAR;
        break;

        case OP_PLUS:
        *code += OP_POSPLUS - OP_PLUS;
        break;

        case OP_MINPLUS:
        *code += OP_POSPLUS - OP_MINPLUS;
        break;

        case OP_QUERY:
        *code += OP_POSQUERY - OP_QUERY;
        break;

        case OP_MINQUERY:
        *code += OP_POSQUERY - OP_MINQUERY;
        break;

        case OP_UPTO:
        *code += OP_POSUPTO - OP_UPTO;
        break;

        case OP_MINUPTO:
        *code += OP_POSUPTO - OP_MINUPTO;
        break;
        }
      }
    c = *code;
    }
  else if (c == OP_CLASS || c == OP_NCLASS || c == OP_XCLASS)
    {
#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
    if (c == OP_XCLASS)
      repeat_opcode = code + GET(code, 1);
    else
#endif
      repeat_opcode = code + 1 + (32 / sizeof(pcre_uchar));

    c = *repeat_opcode;
    if (c >= OP_CRSTAR && c <= OP_CRMINRANGE)
      {
      /* end must not be NULL. */
      end = get_chr_property_list(code, utf, cd->fcc, list);

      list[1] = (c & 1) == 0;

      rec_limit = 1000;
      if (compare_opcodes(end, utf, cd, list, end, &rec_limit))
        {
        switch (c)
          {
          case OP_CRSTAR:
          case OP_CRMINSTAR:
          *repeat_opcode = OP_CRPOSSTAR;
          break;

          case OP_CRPLUS:
          case OP_CRMINPLUS:
          *repeat_opcode = OP_CRPOSPLUS;
          break;

          case OP_CRQUERY:
          case OP_CRMINQUERY:
          *repeat_opcode = OP_CRPOSQUERY;
          break;

          case OP_CRRANGE:
          case OP_CRMINRANGE:
          *repeat_opcode = OP_CRPOSRANGE;
          break;
          }
        }
      }
    c = *code;
    }

  switch(c)
    {
    case OP_END:
    return;

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

    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    case OP_TYPEEXACT:
    case OP_TYPEPOSUPTO:
    if (code[1 + IMM2_SIZE] == OP_PROP || code[1 + IMM2_SIZE] == OP_NOTPROP)
      code += 2;
    break;

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
    case OP_XCLASS:
    code += GET(code, 1);
    break;
#endif

    case OP_MARK:
    case OP_PRUNE_ARG:
    case OP_SKIP_ARG:
    case OP_THEN_ARG:
    code += code[1];
    break;
    }

  /* Add in the fixed length from the table */

  code += PRIV(OP_lengths)[c];

  /* In UTF-8 mode, opcodes that are followed by a character may be followed by
  a multi-byte character. The length in the table is a minimum, so we have to
  arrange to skip the extra bytes. */

#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
  if (utf) switch(c)
    {
    case OP_CHAR:
    case OP_CHARI:
    case OP_NOT:
    case OP_NOTI:
    case OP_STAR:
    case OP_MINSTAR:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_QUERY:
    case OP_MINQUERY:
    case OP_UPTO:
    case OP_MINUPTO:
    case OP_EXACT:
    case OP_POSSTAR:
    case OP_POSPLUS:
    case OP_POSQUERY:
    case OP_POSUPTO:
    case OP_STARI:
    case OP_MINSTARI:
    case OP_PLUSI:
    case OP_MINPLUSI:
    case OP_QUERYI:
    case OP_MINQUERYI:
    case OP_UPTOI:
    case OP_MINUPTOI:
    case OP_EXACTI:
    case OP_POSSTARI:
    case OP_POSPLUSI:
    case OP_POSQUERYI:
    case OP_POSUPTOI:
    case OP_NOTSTAR:
    case OP_NOTMINSTAR:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTQUERY:
    case OP_NOTMINQUERY:
    case OP_NOTUPTO:
    case OP_NOTMINUPTO:
    case OP_NOTEXACT:
    case OP_NOTPOSSTAR:
    case OP_NOTPOSPLUS:
    case OP_NOTPOSQUERY:
    case OP_NOTPOSUPTO:
    case OP_NOTSTARI:
    case OP_NOTMINSTARI:
    case OP_NOTPLUSI:
    case OP_NOTMINPLUSI:
    case OP_NOTQUERYI:
    case OP_NOTMINQUERYI:
    case OP_NOTUPTOI:
    case OP_NOTMINUPTOI:
    case OP_NOTEXACTI:
    case OP_NOTPOSSTARI:
    case OP_NOTPOSPLUSI:
    case OP_NOTPOSQUERYI:
    case OP_NOTPOSUPTOI:
    if (HAS_EXTRALEN(code[-1])) code += GET_EXTRALEN(code[-1]);
    break;
    }
#else
  (void)(utf);  /* Keep compiler happy by referencing function argument */
#endif
  }
}