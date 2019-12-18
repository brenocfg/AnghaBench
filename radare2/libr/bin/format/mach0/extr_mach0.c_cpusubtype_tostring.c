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
typedef  int ut32 ;

/* Variables and functions */
#define  CPU_SUBTYPE_386 223 
#define  CPU_SUBTYPE_486 222 
#define  CPU_SUBTYPE_486SX 221 
#define  CPU_SUBTYPE_ARM64E 220 
#define  CPU_SUBTYPE_ARM64_ALL 219 
#define  CPU_SUBTYPE_ARM64_V8 218 
#define  CPU_SUBTYPE_ARM_ALL 217 
#define  CPU_SUBTYPE_ARM_V4T 216 
#define  CPU_SUBTYPE_ARM_V5 215 
#define  CPU_SUBTYPE_ARM_V6 214 
#define  CPU_SUBTYPE_ARM_V7 213 
#define  CPU_SUBTYPE_ARM_V7EM 212 
#define  CPU_SUBTYPE_ARM_V7F 211 
#define  CPU_SUBTYPE_ARM_V7K 210 
#define  CPU_SUBTYPE_ARM_V7M 209 
#define  CPU_SUBTYPE_ARM_V7S 208 
#define  CPU_SUBTYPE_ARM_XSCALE 207 
#define  CPU_SUBTYPE_CELERON 206 
#define  CPU_SUBTYPE_CELERON_MOBILE 205 
#define  CPU_SUBTYPE_HPPA_7100 204 
#define  CPU_SUBTYPE_HPPA_7100LC 203 
#define  CPU_SUBTYPE_I860_860 202 
#define  CPU_SUBTYPE_I860_ALL 201 
#define  CPU_SUBTYPE_ITANIUM 200 
#define  CPU_SUBTYPE_ITANIUM_2 199 
#define  CPU_SUBTYPE_MC68030 198 
#define  CPU_SUBTYPE_MC68030_ONLY 197 
#define  CPU_SUBTYPE_MC68040 196 
#define  CPU_SUBTYPE_MC88000_ALL 195 
#define  CPU_SUBTYPE_MC88100 194 
#define  CPU_SUBTYPE_MC88110 193 
#define  CPU_SUBTYPE_MC98000_ALL 192 
#define  CPU_SUBTYPE_MC98601 191 
#define  CPU_SUBTYPE_MIPS_ALL 190 
#define  CPU_SUBTYPE_MIPS_R2000 189 
#define  CPU_SUBTYPE_MIPS_R2000a 188 
#define  CPU_SUBTYPE_MIPS_R2300 187 
#define  CPU_SUBTYPE_MIPS_R2600 186 
#define  CPU_SUBTYPE_MIPS_R2800 185 
#define  CPU_SUBTYPE_MIPS_R3000 184 
#define  CPU_SUBTYPE_MIPS_R3000a 183 
#define  CPU_SUBTYPE_PENT 182 
#define  CPU_SUBTYPE_PENTII_M3 181 
#define  CPU_SUBTYPE_PENTII_M5 180 
#define  CPU_SUBTYPE_PENTIUM_3 179 
#define  CPU_SUBTYPE_PENTIUM_3_M 178 
#define  CPU_SUBTYPE_PENTIUM_3_XEON 177 
#define  CPU_SUBTYPE_PENTIUM_4 176 
#define  CPU_SUBTYPE_PENTIUM_4_M 175 
#define  CPU_SUBTYPE_PENTIUM_M 174 
#define  CPU_SUBTYPE_PENTPRO 173 
#define  CPU_SUBTYPE_POWERPC_601 172 
#define  CPU_SUBTYPE_POWERPC_602 171 
#define  CPU_SUBTYPE_POWERPC_603 170 
#define  CPU_SUBTYPE_POWERPC_603e 169 
#define  CPU_SUBTYPE_POWERPC_603ev 168 
#define  CPU_SUBTYPE_POWERPC_604 167 
#define  CPU_SUBTYPE_POWERPC_604e 166 
#define  CPU_SUBTYPE_POWERPC_620 165 
#define  CPU_SUBTYPE_POWERPC_7400 164 
#define  CPU_SUBTYPE_POWERPC_7450 163 
#define  CPU_SUBTYPE_POWERPC_750 162 
#define  CPU_SUBTYPE_POWERPC_970 161 
#define  CPU_SUBTYPE_POWERPC_ALL 160 
#define  CPU_SUBTYPE_SPARC_ALL 159 
#define  CPU_SUBTYPE_UVAXI 158 
#define  CPU_SUBTYPE_UVAXII 157 
#define  CPU_SUBTYPE_UVAXIII 156 
#define  CPU_SUBTYPE_VAX730 155 
#define  CPU_SUBTYPE_VAX750 154 
#define  CPU_SUBTYPE_VAX780 153 
#define  CPU_SUBTYPE_VAX785 152 
#define  CPU_SUBTYPE_VAX8200 151 
#define  CPU_SUBTYPE_VAX8500 150 
#define  CPU_SUBTYPE_VAX8600 149 
#define  CPU_SUBTYPE_VAX8650 148 
#define  CPU_SUBTYPE_VAX8800 147 
#define  CPU_SUBTYPE_VAX_ALL 146 
#define  CPU_SUBTYPE_X86_64_ALL 145 
#define  CPU_SUBTYPE_X86_ARCH1 144 
#define  CPU_SUBTYPE_XEON 143 
#define  CPU_SUBTYPE_XEON_MP 142 
#define  CPU_TYPE_ARM 141 
#define  CPU_TYPE_ARM64 140 
#define  CPU_TYPE_HPPA 139 
#define  CPU_TYPE_I386 138 
#define  CPU_TYPE_I860 137 
#define  CPU_TYPE_MC680x0 136 
#define  CPU_TYPE_MC88000 135 
#define  CPU_TYPE_MC98000 134 
#define  CPU_TYPE_MIPS 133 
#define  CPU_TYPE_POWERPC 132 
#define  CPU_TYPE_POWERPC64 131 
#define  CPU_TYPE_SPARC 130 
#define  CPU_TYPE_VAX 129 
#define  CPU_TYPE_X86_64 128 
 int /*<<< orphan*/  eprintf (char*,int) ; 

__attribute__((used)) static const char *cpusubtype_tostring (ut32 cputype, ut32 cpusubtype) {
	switch (cputype) {
	case CPU_TYPE_VAX:
		switch (cpusubtype) {
		case CPU_SUBTYPE_VAX_ALL:	return "all";
		case CPU_SUBTYPE_VAX780:	return "vax780";
		case CPU_SUBTYPE_VAX785:	return "vax785";
		case CPU_SUBTYPE_VAX750:	return "vax750";
		case CPU_SUBTYPE_VAX730:	return "vax730";
		case CPU_SUBTYPE_UVAXI:		return "uvaxI";
		case CPU_SUBTYPE_UVAXII:	return "uvaxII";
		case CPU_SUBTYPE_VAX8200:	return "vax8200";
		case CPU_SUBTYPE_VAX8500:	return "vax8500";
		case CPU_SUBTYPE_VAX8600:	return "vax8600";
		case CPU_SUBTYPE_VAX8650:	return "vax8650";
		case CPU_SUBTYPE_VAX8800:	return "vax8800";
		case CPU_SUBTYPE_UVAXIII:	return "uvaxIII";
		default:			return "Unknown vax subtype";
		}
	case CPU_TYPE_MC680x0:
		switch (cpusubtype) {
		case CPU_SUBTYPE_MC68030:	return "mc68030";
		case CPU_SUBTYPE_MC68040:	return "mc68040";
		case CPU_SUBTYPE_MC68030_ONLY:	return "mc68030 only";
		default:			return "Unknown mc680x0 subtype";
		}
	case CPU_TYPE_I386:
		switch (cpusubtype) {
		case CPU_SUBTYPE_386: 			return "386";
		case CPU_SUBTYPE_486: 			return "486";
		case CPU_SUBTYPE_486SX: 		return "486sx";
		case CPU_SUBTYPE_PENT: 			return "Pentium";
		case CPU_SUBTYPE_PENTPRO: 		return "Pentium Pro";
		case CPU_SUBTYPE_PENTII_M3: 		return "Pentium 3 M3";
		case CPU_SUBTYPE_PENTII_M5: 		return "Pentium 3 M5";
		case CPU_SUBTYPE_CELERON: 		return "Celeron";
		case CPU_SUBTYPE_CELERON_MOBILE:	return "Celeron Mobile";
		case CPU_SUBTYPE_PENTIUM_3:		return "Pentium 3";
		case CPU_SUBTYPE_PENTIUM_3_M:		return "Pentium 3 M";
		case CPU_SUBTYPE_PENTIUM_3_XEON:	return "Pentium 3 Xeon";
		case CPU_SUBTYPE_PENTIUM_M:		return "Pentium Mobile";
		case CPU_SUBTYPE_PENTIUM_4:		return "Pentium 4";
		case CPU_SUBTYPE_PENTIUM_4_M:		return "Pentium 4 M";
		case CPU_SUBTYPE_ITANIUM:		return "Itanium";
		case CPU_SUBTYPE_ITANIUM_2:		return "Itanium 2";
		case CPU_SUBTYPE_XEON:			return "Xeon";
		case CPU_SUBTYPE_XEON_MP:		return "Xeon MP";
		default:				return "Unknown i386 subtype";
		}
	case CPU_TYPE_X86_64:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_X86_64_ALL:	return "x86 64 all";
		case CPU_SUBTYPE_X86_ARCH1:	return "x86 arch 1";
		default:			return "Unknown x86 subtype";
		}
	case CPU_TYPE_MC88000:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_MC88000_ALL:	return "all";
		case CPU_SUBTYPE_MC88100:	return "mc88100";
		case CPU_SUBTYPE_MC88110:	return "mc88110";
		default:			return "Unknown mc88000 subtype";
		}
	case CPU_TYPE_MC98000:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_MC98000_ALL:	return "all";
		case CPU_SUBTYPE_MC98601:	return "mc98601";
		default:			return "Unknown mc98000 subtype";
		}
	case CPU_TYPE_HPPA:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_HPPA_7100:	return "hppa7100";
		case CPU_SUBTYPE_HPPA_7100LC:	return "hppa7100LC";
		default:			return "Unknown hppa subtype";
		}
	case CPU_TYPE_ARM64:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_ARM64_ALL:	return "all";
		case CPU_SUBTYPE_ARM64_V8:	return "arm64v8";
		case CPU_SUBTYPE_ARM64E:	return "arm64e";
		default:			return "Unknown arm64 subtype";
		}
		return "v8";
	case CPU_TYPE_ARM:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_ARM_ALL:
			return "all";
		case CPU_SUBTYPE_ARM_V4T:
			return "v4t";
		case CPU_SUBTYPE_ARM_V5:
			return "v5";
		case CPU_SUBTYPE_ARM_V6:
			return "v6";
		case CPU_SUBTYPE_ARM_XSCALE:
			return "xscale";
		case CPU_SUBTYPE_ARM_V7:
			return "v7";
		case CPU_SUBTYPE_ARM_V7F:
			return "v7f";
		case CPU_SUBTYPE_ARM_V7S:
			return "v7s";
		case CPU_SUBTYPE_ARM_V7K:
			return "v7k";
		case CPU_SUBTYPE_ARM_V7M:
			return "v7m";
		case CPU_SUBTYPE_ARM_V7EM:
			return "v7em";
		default:
			eprintf ("Unknown arm subtype %d\n", cpusubtype & 0xff);
			return "unknown arm subtype";
		}
	case CPU_TYPE_SPARC:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_SPARC_ALL:	return "all";
		default:			return "Unknown sparc subtype";
		}
	case CPU_TYPE_MIPS:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_MIPS_ALL:	return "all";
		case CPU_SUBTYPE_MIPS_R2300:	return "r2300";
		case CPU_SUBTYPE_MIPS_R2600:	return "r2600";
		case CPU_SUBTYPE_MIPS_R2800:	return "r2800";
		case CPU_SUBTYPE_MIPS_R2000a:	return "r2000a";
		case CPU_SUBTYPE_MIPS_R2000:	return "r2000";
		case CPU_SUBTYPE_MIPS_R3000a:	return "r3000a";
		case CPU_SUBTYPE_MIPS_R3000:	return "r3000";
		default:			return "Unknown mips subtype";
		}
	case CPU_TYPE_I860:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_I860_ALL:	return "all";
		case CPU_SUBTYPE_I860_860:	return "860";
		default:			return "Unknown i860 subtype";
		}
	case CPU_TYPE_POWERPC:
	case CPU_TYPE_POWERPC64:
		switch (cpusubtype & 0xff) {
		case CPU_SUBTYPE_POWERPC_ALL:	return "all";
		case CPU_SUBTYPE_POWERPC_601:	return "601";
		case CPU_SUBTYPE_POWERPC_602:	return "602";
		case CPU_SUBTYPE_POWERPC_603:	return "603";
		case CPU_SUBTYPE_POWERPC_603e:	return "603e";
		case CPU_SUBTYPE_POWERPC_603ev:	return "603ev";
		case CPU_SUBTYPE_POWERPC_604:	return "604";
		case CPU_SUBTYPE_POWERPC_604e:	return "604e";
		case CPU_SUBTYPE_POWERPC_620:	return "620";
		case CPU_SUBTYPE_POWERPC_750:	return "750";
		case CPU_SUBTYPE_POWERPC_7400:	return "7400";
		case CPU_SUBTYPE_POWERPC_7450:	return "7450";
		case CPU_SUBTYPE_POWERPC_970:	return "970";
		default:			return "Unknown ppc subtype";
		}
	}
	return "Unknown cputype";
}