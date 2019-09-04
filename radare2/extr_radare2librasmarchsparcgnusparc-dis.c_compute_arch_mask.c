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
 int SPARC_OPCODE_ARCH_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_SPARCLET ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_SPARCLITE ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_V8 ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_V9 ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_V9A ; 
 int /*<<< orphan*/  SPARC_OPCODE_ARCH_V9B ; 
 int /*<<< orphan*/  abort () ; 
#define  bfd_mach_sparc 137 
#define  bfd_mach_sparc_sparclet 136 
#define  bfd_mach_sparc_sparclite 135 
#define  bfd_mach_sparc_sparclite_le 134 
#define  bfd_mach_sparc_v8plus 133 
#define  bfd_mach_sparc_v8plusa 132 
#define  bfd_mach_sparc_v8plusb 131 
#define  bfd_mach_sparc_v9 130 
#define  bfd_mach_sparc_v9a 129 
#define  bfd_mach_sparc_v9b 128 

__attribute__((used)) static int
compute_arch_mask (unsigned long mach)
{
  switch (mach)
    {
    case 0 :
    case bfd_mach_sparc :
      return SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_V8);
    case bfd_mach_sparc_sparclet :
      return SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_SPARCLET);
    case bfd_mach_sparc_sparclite :
    case bfd_mach_sparc_sparclite_le :
      /* sparclites insns are recognized by default (because that's how
	 they've always been treated, for better or worse).  Kludge this by
	 indicating generic v8 is also selected.  */
      return (SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_SPARCLITE)
	      | SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_V8));
    case bfd_mach_sparc_v8plus :
    case bfd_mach_sparc_v9 :
      return SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_V9);
    case bfd_mach_sparc_v8plusa :
    case bfd_mach_sparc_v9a :
      return SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_V9A);
    case bfd_mach_sparc_v8plusb :
    case bfd_mach_sparc_v9b :
      return SPARC_OPCODE_ARCH_MASK (SPARC_OPCODE_ARCH_V9B);
    }
  abort ();
}