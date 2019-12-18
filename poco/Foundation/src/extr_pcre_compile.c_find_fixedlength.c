#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* group; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ recurse_check ;
typedef  int pcre_uchar ;
struct TYPE_6__ {scalar_t__ start_code; } ;
typedef  TYPE_2__ compile_data ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GET (int*,int) ; 
 int GET2 (int*,int) ; 
 int /*<<< orphan*/  GET_EXTRALEN (int) ; 
 int /*<<< orphan*/  HAS_EXTRALEN (int) ; 
 int IMM2_SIZE ; 
 int LINK_SIZE ; 
#define  OP_ACCEPT 289 
#define  OP_ALLANY 288 
#define  OP_ALT 287 
#define  OP_ANY 286 
#define  OP_ANYBYTE 285 
#define  OP_ANYNL 284 
#define  OP_ASSERT 283 
#define  OP_ASSERTBACK 282 
#define  OP_ASSERTBACK_NOT 281 
#define  OP_ASSERT_ACCEPT 280 
#define  OP_ASSERT_NOT 279 
#define  OP_BRA 278 
#define  OP_BRAMINZERO 277 
#define  OP_BRAPOS 276 
#define  OP_BRAPOSZERO 275 
#define  OP_BRAZERO 274 
#define  OP_CALLOUT 273 
#define  OP_CBRA 272 
#define  OP_CBRAPOS 271 
#define  OP_CHAR 270 
#define  OP_CHARI 269 
#define  OP_CIRC 268 
#define  OP_CIRCM 267 
#define  OP_CLASS 266 
#define  OP_CLOSE 265 
#define  OP_COMMIT 264 
#define  OP_COND 263 
#define  OP_CREF 262 
#define  OP_CRMINPLUS 261 
#define  OP_CRMINQUERY 260 
#define  OP_CRMINRANGE 259 
#define  OP_CRMINSTAR 258 
#define  OP_CRPLUS 257 
#define  OP_CRPOSPLUS 256 
#define  OP_CRPOSQUERY 255 
#define  OP_CRPOSRANGE 254 
#define  OP_CRPOSSTAR 253 
#define  OP_CRQUERY 252 
#define  OP_CRRANGE 251 
#define  OP_CRSTAR 250 
#define  OP_DEF 249 
#define  OP_DIGIT 248 
#define  OP_DNCREF 247 
#define  OP_DNREF 246 
#define  OP_DNREFI 245 
#define  OP_DNRREF 244 
#define  OP_DOLL 243 
#define  OP_DOLLM 242 
#define  OP_END 241 
#define  OP_EOD 240 
#define  OP_EODN 239 
#define  OP_EXACT 238 
#define  OP_EXACTI 237 
#define  OP_EXTUNI 236 
#define  OP_FAIL 235 
#define  OP_HSPACE 234 
#define  OP_KET 233 
#define  OP_KETRMAX 232 
#define  OP_KETRMIN 231 
#define  OP_KETRPOS 230 
#define  OP_MARK 229 
#define  OP_MINPLUS 228 
#define  OP_MINPLUSI 227 
#define  OP_MINQUERY 226 
#define  OP_MINQUERYI 225 
#define  OP_MINSTAR 224 
#define  OP_MINSTARI 223 
#define  OP_MINUPTO 222 
#define  OP_MINUPTOI 221 
#define  OP_NCLASS 220 
#define  OP_NOT 219 
#define  OP_NOTEXACT 218 
#define  OP_NOTEXACTI 217 
#define  OP_NOTI 216 
#define  OP_NOTMINPLUS 215 
#define  OP_NOTMINPLUSI 214 
#define  OP_NOTMINQUERY 213 
#define  OP_NOTMINQUERYI 212 
#define  OP_NOTMINSTAR 211 
#define  OP_NOTMINSTARI 210 
#define  OP_NOTMINUPTO 209 
#define  OP_NOTMINUPTOI 208 
#define  OP_NOTPLUS 207 
#define  OP_NOTPLUSI 206 
#define  OP_NOTPOSPLUS 205 
#define  OP_NOTPOSPLUSI 204 
#define  OP_NOTPOSQUERY 203 
#define  OP_NOTPOSQUERYI 202 
#define  OP_NOTPOSSTAR 201 
#define  OP_NOTPOSSTARI 200 
#define  OP_NOTPOSUPTO 199 
#define  OP_NOTPOSUPTOI 198 
#define  OP_NOTPROP 197 
#define  OP_NOTQUERY 196 
#define  OP_NOTQUERYI 195 
#define  OP_NOTSTAR 194 
#define  OP_NOTSTARI 193 
#define  OP_NOTUPTO 192 
#define  OP_NOTUPTOI 191 
#define  OP_NOT_DIGIT 190 
#define  OP_NOT_HSPACE 189 
#define  OP_NOT_VSPACE 188 
#define  OP_NOT_WHITESPACE 187 
#define  OP_NOT_WORDCHAR 186 
#define  OP_NOT_WORD_BOUNDARY 185 
#define  OP_ONCE 184 
#define  OP_ONCE_NC 183 
#define  OP_PLUS 182 
#define  OP_PLUSI 181 
#define  OP_POSPLUS 180 
#define  OP_POSPLUSI 179 
#define  OP_POSQUERY 178 
#define  OP_POSQUERYI 177 
#define  OP_POSSTAR 176 
#define  OP_POSSTARI 175 
#define  OP_POSUPTO 174 
#define  OP_POSUPTOI 173 
#define  OP_PROP 172 
#define  OP_PRUNE 171 
#define  OP_PRUNE_ARG 170 
#define  OP_QUERY 169 
#define  OP_QUERYI 168 
#define  OP_RECURSE 167 
#define  OP_REF 166 
#define  OP_REFI 165 
#define  OP_REVERSE 164 
#define  OP_RREF 163 
#define  OP_SBRA 162 
#define  OP_SBRAPOS 161 
#define  OP_SCBRA 160 
#define  OP_SCBRAPOS 159 
#define  OP_SCOND 158 
#define  OP_SET_SOM 157 
#define  OP_SKIP 156 
#define  OP_SKIPZERO 155 
#define  OP_SKIP_ARG 154 
#define  OP_SOD 153 
#define  OP_SOM 152 
#define  OP_STAR 151 
#define  OP_STARI 150 
#define  OP_THEN 149 
#define  OP_THEN_ARG 148 
#define  OP_TYPEEXACT 147 
#define  OP_TYPEMINPLUS 146 
#define  OP_TYPEMINQUERY 145 
#define  OP_TYPEMINSTAR 144 
#define  OP_TYPEMINUPTO 143 
#define  OP_TYPEPLUS 142 
#define  OP_TYPEPOSPLUS 141 
#define  OP_TYPEPOSQUERY 140 
#define  OP_TYPEPOSSTAR 139 
#define  OP_TYPEPOSUPTO 138 
#define  OP_TYPEQUERY 137 
#define  OP_TYPESTAR 136 
#define  OP_TYPEUPTO 135 
#define  OP_UPTO 134 
#define  OP_UPTOI 133 
#define  OP_VSPACE 132 
#define  OP_WHITESPACE 131 
#define  OP_WORDCHAR 130 
#define  OP_WORD_BOUNDARY 129 
#define  OP_XCLASS 128 
 int /*<<< orphan*/  OP_lengths ; 
 int* PRIV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_fixedlength(pcre_uchar *code, BOOL utf, BOOL atend, compile_data *cd,
  recurse_check *recurses)
{
int length = -1;
recurse_check this_recurse;
register int branchlength = 0;
register pcre_uchar *cc = code + 1 + LINK_SIZE;

/* Scan along the opcodes for this branch. If we get to the end of the
branch, check the length against that of the other branches. */

for (;;)
  {
  int d;
  pcre_uchar *ce, *cs;
  register pcre_uchar op = *cc;

  switch (op)
    {
    /* We only need to continue for OP_CBRA (normal capturing bracket) and
    OP_BRA (normal non-capturing bracket) because the other variants of these
    opcodes are all concerned with unlimited repeated groups, which of course
    are not of fixed length. */

    case OP_CBRA:
    case OP_BRA:
    case OP_ONCE:
    case OP_ONCE_NC:
    case OP_COND:
    d = find_fixedlength(cc + ((op == OP_CBRA)? IMM2_SIZE : 0), utf, atend, cd,
      recurses);
    if (d < 0) return d;
    branchlength += d;
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    cc += 1 + LINK_SIZE;
    break;

    /* Reached end of a branch; if it's a ket it is the end of a nested call.
    If it's ALT it is an alternation in a nested call. An ACCEPT is effectively
    an ALT. If it is END it's the end of the outer call. All can be handled by
    the same code. Note that we must not include the OP_KETRxxx opcodes here,
    because they all imply an unlimited repeat. */

    case OP_ALT:
    case OP_KET:
    case OP_END:
    case OP_ACCEPT:
    case OP_ASSERT_ACCEPT:
    if (length < 0) length = branchlength;
      else if (length != branchlength) return -1;
    if (*cc != OP_ALT) return length;
    cc += 1 + LINK_SIZE;
    branchlength = 0;
    break;

    /* A true recursion implies not fixed length, but a subroutine call may
    be OK. If the subroutine is a forward reference, we can't deal with
    it until the end of the pattern, so return -3. */

    case OP_RECURSE:
    if (!atend) return -3;
    cs = ce = (pcre_uchar *)cd->start_code + GET(cc, 1);  /* Start subpattern */
    do ce += GET(ce, 1); while (*ce == OP_ALT);           /* End subpattern */
    if (cc > cs && cc < ce) return -1;                    /* Recursion */
    else   /* Check for mutual recursion */
      {
      recurse_check *r = recurses;
      for (r = recurses; r != NULL; r = r->prev) if (r->group == cs) break;
      if (r != NULL) return -1;   /* Mutual recursion */
      }
    this_recurse.prev = recurses;
    this_recurse.group = cs;
    d = find_fixedlength(cs + IMM2_SIZE, utf, atend, cd, &this_recurse);
    if (d < 0) return d;
    branchlength += d;
    cc += 1 + LINK_SIZE;
    break;

    /* Skip over assertive subpatterns */

    case OP_ASSERT:
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    cc += 1 + LINK_SIZE;
    break;

    /* Skip over things that don't match chars */

    case OP_MARK:
    case OP_PRUNE_ARG:
    case OP_SKIP_ARG:
    case OP_THEN_ARG:
    cc += cc[1] + PRIV(OP_lengths)[*cc];
    break;

    case OP_CALLOUT:
    case OP_CIRC:
    case OP_CIRCM:
    case OP_CLOSE:
    case OP_COMMIT:
    case OP_CREF:
    case OP_DEF:
    case OP_DNCREF:
    case OP_DNRREF:
    case OP_DOLL:
    case OP_DOLLM:
    case OP_EOD:
    case OP_EODN:
    case OP_FAIL:
    case OP_NOT_WORD_BOUNDARY:
    case OP_PRUNE:
    case OP_REVERSE:
    case OP_RREF:
    case OP_SET_SOM:
    case OP_SKIP:
    case OP_SOD:
    case OP_SOM:
    case OP_THEN:
    case OP_WORD_BOUNDARY:
    cc += PRIV(OP_lengths)[*cc];
    break;

    /* Handle literal characters */

    case OP_CHAR:
    case OP_CHARI:
    case OP_NOT:
    case OP_NOTI:
    branchlength++;
    cc += 2;
#ifdef SUPPORT_UTF
    if (utf && HAS_EXTRALEN(cc[-1])) cc += GET_EXTRALEN(cc[-1]);
#endif
    break;

    /* Handle exact repetitions. The count is already in characters, but we
    need to skip over a multibyte character in UTF8 mode.  */

    case OP_EXACT:
    case OP_EXACTI:
    case OP_NOTEXACT:
    case OP_NOTEXACTI:
    branchlength += (int)GET2(cc,1);
    cc += 2 + IMM2_SIZE;
#ifdef SUPPORT_UTF
    if (utf && HAS_EXTRALEN(cc[-1])) cc += GET_EXTRALEN(cc[-1]);
#endif
    break;

    case OP_TYPEEXACT:
    branchlength += GET2(cc,1);
    if (cc[1 + IMM2_SIZE] == OP_PROP || cc[1 + IMM2_SIZE] == OP_NOTPROP)
      cc += 2;
    cc += 1 + IMM2_SIZE + 1;
    break;

    /* Handle single-char matchers */

    case OP_PROP:
    case OP_NOTPROP:
    cc += 2;
    /* Fall through */

    case OP_HSPACE:
    case OP_VSPACE:
    case OP_NOT_HSPACE:
    case OP_NOT_VSPACE:
    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:
    case OP_ANY:
    case OP_ALLANY:
    branchlength++;
    cc++;
    break;

    /* The single-byte matcher isn't allowed. This only happens in UTF-8 mode;
    otherwise \C is coded as OP_ALLANY. */

    case OP_ANYBYTE:
    return -2;

    /* Check a class for variable quantification */

    case OP_CLASS:
    case OP_NCLASS:
#if defined SUPPORT_UTF || defined COMPILE_PCRE16 || defined COMPILE_PCRE32
    case OP_XCLASS:
    /* The original code caused an unsigned overflow in 64 bit systems,
    so now we use a conditional statement. */
    if (op == OP_XCLASS)
      cc += GET(cc, 1);
    else
      cc += PRIV(OP_lengths)[OP_CLASS];
#else
    cc += PRIV(OP_lengths)[OP_CLASS];
#endif

    switch (*cc)
      {
      case OP_CRSTAR:
      case OP_CRMINSTAR:
      case OP_CRPLUS:
      case OP_CRMINPLUS:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      case OP_CRPOSSTAR:
      case OP_CRPOSPLUS:
      case OP_CRPOSQUERY:
      return -1;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      case OP_CRPOSRANGE:
      if (GET2(cc,1) != GET2(cc,1+IMM2_SIZE)) return -1;
      branchlength += (int)GET2(cc,1);
      cc += 1 + 2 * IMM2_SIZE;
      break;

      default:
      branchlength++;
      }
    break;

    /* Anything else is variable length */

    case OP_ANYNL:
    case OP_BRAMINZERO:
    case OP_BRAPOS:
    case OP_BRAPOSZERO:
    case OP_BRAZERO:
    case OP_CBRAPOS:
    case OP_EXTUNI:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_KETRPOS:
    case OP_MINPLUS:
    case OP_MINPLUSI:
    case OP_MINQUERY:
    case OP_MINQUERYI:
    case OP_MINSTAR:
    case OP_MINSTARI:
    case OP_MINUPTO:
    case OP_MINUPTOI:
    case OP_NOTMINPLUS:
    case OP_NOTMINPLUSI:
    case OP_NOTMINQUERY:
    case OP_NOTMINQUERYI:
    case OP_NOTMINSTAR:
    case OP_NOTMINSTARI:
    case OP_NOTMINUPTO:
    case OP_NOTMINUPTOI:
    case OP_NOTPLUS:
    case OP_NOTPLUSI:
    case OP_NOTPOSPLUS:
    case OP_NOTPOSPLUSI:
    case OP_NOTPOSQUERY:
    case OP_NOTPOSQUERYI:
    case OP_NOTPOSSTAR:
    case OP_NOTPOSSTARI:
    case OP_NOTPOSUPTO:
    case OP_NOTPOSUPTOI:
    case OP_NOTQUERY:
    case OP_NOTQUERYI:
    case OP_NOTSTAR:
    case OP_NOTSTARI:
    case OP_NOTUPTO:
    case OP_NOTUPTOI:
    case OP_PLUS:
    case OP_PLUSI:
    case OP_POSPLUS:
    case OP_POSPLUSI:
    case OP_POSQUERY:
    case OP_POSQUERYI:
    case OP_POSSTAR:
    case OP_POSSTARI:
    case OP_POSUPTO:
    case OP_POSUPTOI:
    case OP_QUERY:
    case OP_QUERYI:
    case OP_REF:
    case OP_REFI:
    case OP_DNREF:
    case OP_DNREFI:
    case OP_SBRA:
    case OP_SBRAPOS:
    case OP_SCBRA:
    case OP_SCBRAPOS:
    case OP_SCOND:
    case OP_SKIPZERO:
    case OP_STAR:
    case OP_STARI:
    case OP_TYPEMINPLUS:
    case OP_TYPEMINQUERY:
    case OP_TYPEMINSTAR:
    case OP_TYPEMINUPTO:
    case OP_TYPEPLUS:
    case OP_TYPEPOSPLUS:
    case OP_TYPEPOSQUERY:
    case OP_TYPEPOSSTAR:
    case OP_TYPEPOSUPTO:
    case OP_TYPEQUERY:
    case OP_TYPESTAR:
    case OP_TYPEUPTO:
    case OP_UPTO:
    case OP_UPTOI:
    return -1;

    /* Catch unrecognized opcodes so that when new ones are added they
    are not forgotten, as has happened in the past. */

    default:
    return -4;
    }
  }
/* Control never gets here */
}