#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
struct TYPE_6__ {int flags; char enc_letter; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ hexagon_operand ;
struct TYPE_7__ {char* syntax; int attributes; int /*<<< orphan*/  enc; } ;
typedef  TYPE_2__ hexagon_opcode ;
typedef  int hexagon_insn ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int A_IT_EXTENDER ; 
 int EXTENDABLE_LOWER_CASE_IMMEDIATE ; 
 int EXTENDABLE_UPPER_CASE_IMMEDIATE ; 
 int FALSE ; 
#define  HEXAGON_END_LOOP 131 
#define  HEXAGON_END_NOT 130 
#define  HEXAGON_END_PACKET 129 
 int HEXAGON_END_PACKET_GET (int) ; 
#define  HEXAGON_END_PAIR 128 
 int HEXAGON_OPERAND_IS_IMMEDIATE ; 
 int HEXAGON_OPERAND_IS_KXED ; 
 int HEXAGON_OPERAND_IS_KXER ; 
 int /*<<< orphan*/  ISBLANK (char) ; 
 scalar_t__ ISLOWER (char) ; 
 scalar_t__ ISUPPER (char) ; 
 int PACKET_BEGIN ; 
 int PACKET_END ; 
 char* PACKET_END_INNER ; 
 char* PACKET_END_OUTER ; 
 char TOUPPER (char) ; 
 int TRUE ; 
 char* hexagon_dis_operand (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char**) ; 
 size_t hexagon_operand_count ; 
 TYPE_1__* hexagon_operands ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,size_t) ; 

int
hexagon_dis_opcode
(char *buf, hexagon_insn insn, bfd_vma address,
 const hexagon_opcode *opcode, char **errmsg)
{
  static char temp [40];
  static int in_packet;
  static int end_inner;
  static int end_outer;
  static bfd_vma packet_addr;
  hexagon_insn packet_bits = HEXAGON_END_PACKET_GET (insn);
  int end_packet = FALSE;
  char *src = opcode->syntax;
  char *dst = buf;

  switch (packet_bits)
    {
      case HEXAGON_END_PACKET:
      case HEXAGON_END_PAIR:
        if (in_packet)
          dst += sprintf (dst, "  ");
        else
          packet_addr = address;
        end_packet = TRUE;
        break;

      case HEXAGON_END_LOOP:
      case HEXAGON_END_NOT:
        if (!in_packet)
          {
            dst += sprintf (dst, "%c ", PACKET_BEGIN);
            packet_addr = address;
          }
        else
          dst += sprintf (dst, "  ");

        ++in_packet;

        if (packet_bits == HEXAGON_END_LOOP)
          {
            if (in_packet == 1) end_inner = TRUE;
            if (in_packet == 2) end_outer = TRUE;
          }
        break;

      default:
        if (errmsg)
          {
            snprintf (temp, sizeof (temp), "invalid packet bits: %.8x", packet_bits);
            *errmsg = temp;
          }
        return FALSE;
        break;
    }

  while (*src)
    {
      /* EJP: ignore +I */
      if ((ISUPPER(*src) && (TOUPPER(*src) != 'I')) || *src == '#')
        {
          /* We have an operand */
          int found = FALSE;
          size_t i;

          for (i = 0; i < hexagon_operand_count; i++)
            {
              hexagon_operand operand;
              size_t len;

              operand = hexagon_operands [i];
              len = strlen (operand.fmt);

              if (!strncmp (src, operand.fmt, len))
                {
                  found = TRUE;

                  if (opcode->attributes & A_IT_EXTENDER)
                    operand.flags |= HEXAGON_OPERAND_IS_KXER;
                  else if ((operand.flags & HEXAGON_OPERAND_IS_IMMEDIATE)
                           && (((opcode->attributes & EXTENDABLE_LOWER_CASE_IMMEDIATE)
                                && (ISLOWER (operand.enc_letter)))
                               || ((opcode->attributes & EXTENDABLE_UPPER_CASE_IMMEDIATE)
                                   && (ISUPPER (operand.enc_letter)))))
                    /* Not necessarily extended, but maybe so. */
                    operand.flags |= HEXAGON_OPERAND_IS_KXED;
                  dst = hexagon_dis_operand (&operand, insn, address, packet_addr,
                                           opcode->enc, dst, errmsg);
                  if (!dst)
                    {
                      /* Some kind of error! */
                      sprintf (buf, "<unknown insn 0x%08x>", insn);
                      return FALSE;
                    }

                  /* Move past the opcode specifier */
                  src += len;
                  break;
                }
            }

          if (!found)
            {
              sprintf (buf, "<unknown insn 0x%08x>", insn);

              if (errmsg)
                {
                  snprintf (temp, sizeof (temp), "unknown operand: %s", src);
                  *errmsg = temp;
                }
              return FALSE;
            }
        }
      else
        {
          /* Beautify disassembly. */
          switch (*src)
            {
              /* Skip space after. */
              case '(':
              case '!':
                *dst++ = *src++;

                while (ISBLANK (src [0]))
                  src++;
                break;

              /* Delete space before. */
              case ')':
              case '.':
              case ',':
              case ':':
                while (ISBLANK (dst [-1]))
                  dst--;

                *dst++ = *src++;
                break;

              /* Nothing, just copy. */
              default:
                *dst++ = *src++;
                break;
            }
        }
    }

  *dst = '\0';

  if (end_packet)
    {
      if (in_packet)
        {
          dst += sprintf (dst, " %c", PACKET_END);

          if (end_inner)
            dst += sprintf (dst, PACKET_END_INNER);
          if (end_outer)
            dst += sprintf (dst, PACKET_END_OUTER);
        }

      in_packet = FALSE;
      end_inner = FALSE;
      end_outer = FALSE;
    }

  return TRUE;
}