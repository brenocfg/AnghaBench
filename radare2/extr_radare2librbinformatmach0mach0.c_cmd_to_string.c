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
#define  LC_BUILD_VERSION 177 
#define  LC_CODE_SIGNATURE 176 
#define  LC_DATA_IN_CODE 175 
#define  LC_DYLD_ENVIRONMENT 174 
#define  LC_DYLD_INFO 173 
#define  LC_DYLD_INFO_ONLY 172 
#define  LC_DYLIB_CODE_SIGN_DRS 171 
#define  LC_DYSYMTAB 170 
#define  LC_ENCRYPTION_INFO 169 
#define  LC_ENCRYPTION_INFO_64 168 
#define  LC_FUNCTION_STARTS 167 
#define  LC_FVMFILE 166 
#define  LC_IDENT 165 
#define  LC_IDFVMLIB 164 
#define  LC_ID_DYLIB 163 
#define  LC_ID_DYLINKER 162 
#define  LC_LAZY_LOAD_DYLIB 161 
#define  LC_LINKER_OPTIMIZATION_HINT 160 
#define  LC_LINKER_OPTION 159 
#define  LC_LOADFVMLIB 158 
#define  LC_LOAD_DYLIB 157 
#define  LC_LOAD_DYLINKER 156 
#define  LC_LOAD_WEAK_DYLIB 155 
#define  LC_MAIN 154 
#define  LC_NOTE 153 
#define  LC_PREBIND_CKSUM 152 
#define  LC_PREBOUND_DYLIB 151 
#define  LC_PREPAGE 150 
#define  LC_REEXPORT_DYLIB 149 
#define  LC_ROUTINES 148 
#define  LC_ROUTINES_64 147 
#define  LC_RPATH 146 
#define  LC_SEGMENT 145 
#define  LC_SEGMENT_64 144 
#define  LC_SEGMENT_SPLIT_INFO 143 
#define  LC_SOURCE_VERSION 142 
#define  LC_SUB_CLIENT 141 
#define  LC_SUB_FRAMEWORK 140 
#define  LC_SUB_LIBRARY 139 
#define  LC_SUB_UMBRELLA 138 
#define  LC_SYMSEG 137 
#define  LC_SYMTAB 136 
#define  LC_THREAD 135 
#define  LC_TWOLEVEL_HINTS 134 
#define  LC_UNIXTHREAD 133 
#define  LC_UUID 132 
#define  LC_VERSION_MIN_IPHONEOS 131 
#define  LC_VERSION_MIN_MACOSX 130 
#define  LC_VERSION_MIN_TVOS 129 
#define  LC_VERSION_MIN_WATCHOS 128 

__attribute__((used)) static const char *cmd_to_string(ut32 cmd) {
	switch (cmd) {
	case LC_DATA_IN_CODE:
		return "LC_DATA_IN_CODE";
	case LC_CODE_SIGNATURE:
		return "LC_CODE_SIGNATURE";
	case LC_RPATH:
		return "LC_RPATH";
	case LC_TWOLEVEL_HINTS:
		return "LC_TWOLEVEL_HINTS";
	case LC_PREBIND_CKSUM:
		return "LC_PREBIND_CKSUM";
	case LC_SEGMENT:
		return "LC_SEGMENT";
	case LC_SEGMENT_64:
		return "LC_SEGMENT_64";
	case LC_SYMTAB:
		return "LC_SYMTAB";
	case LC_SYMSEG:
		return "LC_SYMSEG";
	case LC_DYSYMTAB:
		return "LC_DYSYMTAB";
	case LC_PREBOUND_DYLIB:
		return "LC_PREBOUND_DYLIB";
	case LC_ROUTINES:
		return "LC_ROUTINES";
	case LC_ROUTINES_64:
		return "LC_ROUTINES_64";
	case LC_SUB_FRAMEWORK:
		return "LC_SUB_FRAMEWORK";
	case LC_SUB_UMBRELLA:
		return "LC_SUB_UMBRELLA";
	case LC_SUB_CLIENT:
		return "LC_SUB_CLIENT";
	case LC_SUB_LIBRARY:
		return "LC_SUB_LIBRARY";
	case LC_FUNCTION_STARTS:
		return "LC_FUNCTION_STARTS";
	case LC_DYLIB_CODE_SIGN_DRS:
		return "LC_DYLIB_CODE_SIGN_DRS";
	case LC_NOTE:
		return "LC_NOTE";
	case LC_BUILD_VERSION:
		return "LC_BUILD_VERSION";
	case LC_VERSION_MIN_MACOSX:
		return "LC_VERSION_MIN_MACOSX";
	case LC_VERSION_MIN_IPHONEOS:
		return "LC_VERSION_MIN_IPHONEOS";
	case LC_VERSION_MIN_TVOS:
		return "LC_VERSION_MIN_TVOS";
	case LC_VERSION_MIN_WATCHOS:
		return "LC_VERSION_MIN_WATCHOS";
	case LC_DYLD_INFO:
		return "LC_DYLD_INFO";
	case LC_DYLD_INFO_ONLY:
		return "LC_DYLD_INFO_ONLY";
	case LC_DYLD_ENVIRONMENT:
		return "LC_DYLD_ENVIRONMENT";
	case LC_SOURCE_VERSION:
		return "LC_SOURCE_VERSION";
	case LC_MAIN:
		return "LC_MAIN";
	case LC_UUID:
		return "LC_UUID";
	case LC_ID_DYLIB:
		return "LC_ID_DYLIB";
	case LC_ID_DYLINKER:
		return "LC_ID_DYLINKER";
	case LC_LAZY_LOAD_DYLIB:
		return "LC_LAZY_LOAD_DYLIB";
	case LC_ENCRYPTION_INFO:
		return "LC_ENCRYPTION_INFO";
	case LC_ENCRYPTION_INFO_64:
		return "LC_ENCRYPTION_INFO_64";
	case LC_SEGMENT_SPLIT_INFO:
		return "LC_SEGMENT_SPLIT_INFO";
	case LC_REEXPORT_DYLIB:
		return "LC_REEXPORT_DYLIB";
	case LC_LINKER_OPTION:
		return "LC_LINKER_OPTION";
	case LC_LINKER_OPTIMIZATION_HINT:
		return "LC_LINKER_OPTIMIZATION_HINT";
	case LC_LOAD_DYLINKER:
		return "LC_LOAD_DYLINKER";
	case LC_LOAD_DYLIB:
		return "LC_LOAD_DYLIB";
	case LC_LOAD_WEAK_DYLIB:
		return "LC_LOAD_WEAK_DYLIB";
	case LC_THREAD:
		return "LC_THREAD";
	case LC_UNIXTHREAD:
		return "LC_UNIXTHREAD";
	case LC_LOADFVMLIB:
		return "LC_LOADFVMLIB";
	case LC_IDFVMLIB:
		return "LC_IDFVMLIB";
	case LC_IDENT:
		return "LC_IDENT";
	case LC_FVMFILE:
		return "LC_FVMFILE";
	case LC_PREPAGE:
		return "LC_PREPAGE";
	}
	return "";
}