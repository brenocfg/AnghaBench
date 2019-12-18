#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* print_address_func ) (scalar_t__,TYPE_1__*) ;} ;
typedef  TYPE_1__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 scalar_t__ NEXTBYTE (unsigned char*) ; 
 scalar_t__ NEXTWORD (unsigned char*) ; 
 int /*<<< orphan*/  abort () ; 
 int print_insn_mode (char const*,int,unsigned char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int
print_insn_arg (const char *d,
		unsigned char *p0,
		bfd_vma addr,	/* PC for this arg to be relative to.  */
		disassemble_info *info)
{
  int arg_len;

  /* Check validity of addressing length.  */
  switch (d[1])
    {
    case 'b' : arg_len = 1;	break;
    case 'd' : arg_len = 8;	break;
    case 'f' : arg_len = 4;	break;
    case 'g' : arg_len = 8;	break;
    case 'h' : arg_len = 16;	break;
    case 'l' : arg_len = 4;	break;
    case 'o' : arg_len = 16;	break;
    case 'w' : arg_len = 2;	break;
    case 'q' : arg_len = 8;	break;
    default  : abort ();
    }

  /* Branches have no mode byte.  */
  if (d[0] == 'b')
    {
      unsigned char *p = p0;

      if (arg_len == 1) {
	      (*info->print_address_func) (addr + 1 + NEXTBYTE (p), info);
      } else {
	      (*info->print_address_func) (addr + 2 + NEXTWORD (p), info);
      }

      return p - p0;
    }

  return print_insn_mode (d, arg_len, p0, addr, info);
}