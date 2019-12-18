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

__attribute__((used)) static const char *cmd_to_pf_definition(ut32 cmd) {
	switch (cmd) {
	case LC_BUILD_VERSION:
		return "mach0_build_version_command";
	case LC_CODE_SIGNATURE:
		return "mach0_code_signature_command";
	case LC_DATA_IN_CODE:
		return "mach0_data_in_code_command";
	case LC_DYLD_INFO:
	case LC_DYLD_INFO_ONLY:
		return "mach0_dyld_info_only_command";
	case LC_DYLD_ENVIRONMENT:
		return NULL;
	case LC_DYLIB_CODE_SIGN_DRS:
		return NULL;
	case LC_DYSYMTAB:
		return "mach0_dysymtab_command";
	case LC_ENCRYPTION_INFO:
		return "mach0_encryption_info_command";
	case LC_ENCRYPTION_INFO_64:
		return "mach0_encryption_info64_command";
	case LC_FUNCTION_STARTS:
		return "mach0_function_starts_command";
	case LC_FVMFILE:
		return NULL;
	case LC_ID_DYLIB:
		return "mach0_id_dylib_command";
	case LC_ID_DYLINKER:
		return "mach0_id_dylinker_command";
	case LC_IDENT:
		return NULL;
	case LC_IDFVMLIB:
		return NULL;
	case LC_LINKER_OPTION:
		return NULL;
	case LC_LINKER_OPTIMIZATION_HINT:
		return NULL;
	case LC_LOAD_DYLINKER:
		return "mach0_load_dylinker_command";
	case LC_LAZY_LOAD_DYLIB:
	case LC_LOAD_WEAK_DYLIB:
	case LC_LOAD_DYLIB:
		return "mach0_dylib_command";
	case LC_LOADFVMLIB:
		return NULL;
	case LC_MAIN:
		return "mach0_entry_point_command";
	case LC_NOTE:
		return NULL;
	case LC_PREBIND_CKSUM:
		return NULL;
	case LC_PREBOUND_DYLIB:
		return NULL;
	case LC_PREPAGE:
		return NULL;
	case LC_REEXPORT_DYLIB:
		return NULL;
	case LC_ROUTINES:
		return NULL;
	case LC_ROUTINES_64:
		return NULL;
	case LC_RPATH:
		return "mach0_rpath_command";
	case LC_SEGMENT:
		return "mach0_segment";
	case LC_SEGMENT_64:
		return "mach0_segment64";
	case LC_SEGMENT_SPLIT_INFO:
		return "mach0_segment_split_info_command";
	case LC_SOURCE_VERSION:
		return "mach0_source_version_command";
	case LC_SUB_FRAMEWORK:
		return NULL;
	case LC_SUB_UMBRELLA:
		return NULL;
	case LC_SUB_CLIENT:
		return NULL;
	case LC_SUB_LIBRARY:
		return NULL;
	case LC_SYMTAB:
		return "mach0_symtab_command";
	case LC_SYMSEG:
		return NULL;
	case LC_TWOLEVEL_HINTS:
		return NULL;
	case LC_UUID:
		return "mach0_uuid_command";
	case LC_VERSION_MIN_MACOSX:
	case LC_VERSION_MIN_IPHONEOS:
	case LC_VERSION_MIN_TVOS:
	case LC_VERSION_MIN_WATCHOS:
		return "mach0_version_min_command";
	case LC_THREAD:
		return NULL;
	case LC_UNIXTHREAD:
		return "mach0_unixthread_command";
	}
	return NULL;
}