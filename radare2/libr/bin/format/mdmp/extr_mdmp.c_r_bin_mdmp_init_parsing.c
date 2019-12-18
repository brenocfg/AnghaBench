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
struct r_bin_mdmp_obj {int /*<<< orphan*/  kv; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_bin_mdmp_init_parsing(struct r_bin_mdmp_obj *obj) {
	/* TODO: Handle unions, can we? */
	/* FIXME: Why are we getting struct missing errors when it finds them */
	sdb_set (obj->kv, "mdmp_mem_state.cparse",
		"enum mdmp_mem_state { MEM_COMMIT=0x1000, "
		"MEM_FREE=0x10000, MEM_RESERVE=0x02000 };", 0);

	sdb_set (obj->kv, "mdmp_mem_type.cparse",
		"enum mdmp_mem_type { MEM_IMAGE=0x1000000, "
		"MEM_MAPPED=0x40000, MEM_PRIVATE=0x20000 };", 0);

	sdb_set (obj->kv, "mdmp_page_protect.cparse",
		"enum mdmp_page_protect { PAGE_NOACCESS=1, "
		"PAGE_READONLY=2, PAGE_READWRITE=4, PAGE_WRITECOPY=8, "
		"PAGE_EXECUTE=0x10, PAGE_EXECUTE_READ=0x20, "
		"PAGE_EXECUTE_READWRITE=0x40, PAGE_EXECUTE_WRITECOPY=0x80, "
		"PAGE_GUARD=0x100, PAGE_NOCACHE=0x200, "
		"PAGE_WRITECOMBINE=0x400, PAGE_TARGETS_INVALID=0x40000000 };",
		0);

	sdb_set (obj->kv, "mdmp_misc1_flags.cparse",
		"enum mdmp_misc1_flags { MINIDUMP_MISC1_PROCESS_ID=1, "
		"MINIDUMP_MISC1_PROCESS_TIMES=2, "
		"MINIDUMP_MISC1_PROCESSOR_POWER_INFO=4 };", 0);

	sdb_set (obj->kv, "mdmp_processor_architecture.cparse",
		"enum mdmp_processor_architecture { "
		"PROCESSOR_ARCHITECTURE_INTEL=0, "
		"PROCESSOR_ARCHITECTURE_ARM=5, "
		"PROCESSOR_ARCHITECTURE_IA64=6, "
		"PROCESSOR_ARCHITECTURE_AMD64=9, "
		"PROCESSOR_ARCHITECTURE_UNKNOWN=0xffff };", 0);

	sdb_set (obj->kv, "mdmp_product_type.cparse",
		"enum mdmp_product_type { "
		"VER_NT_WORKSTATION=1, VER_NT_DOMAIN_CONTROLLER=2, "
		"VER_NT_SERVER=3 };", 0);

	sdb_set (obj->kv, "mdmp_platform_id.cparse",
		"enum mdmp_platform_id { "
		"VER_PLATFORM_WIN32s=0, "
		"VER_PLATFORM_WIN32_WINDOWS=1, "
		"VER_PLATFORM_WIN32_NT=2 };", 0);

	sdb_set (obj->kv, "mdmp_suite_mask.cparse",
		"enum mdmp_suite_mask { "
		"VER_SUITE_SMALLBUSINESS=1, VER_SUITE_ENTERPRISE=2, "
		"VER_SUITE_BACKOFFICE=4, VER_SUITE_TERMINAL=0x10, "
		"VER_SUITE_SMALLBUSINESS_RESTRICTED=0x20, "
		"VER_SUITE_EMBEDDEDNT=0x40, VER_SUITE_DATACENTER=0x80, "
		"VER_SUITE_SINGLEUSERTS=0x100, VER_SUITE_PERSONAL=0x200, "
		"VER_SUITE_BLADE=0x400, VER_SUITE_STORAGE_SERVER=0x2000, "
		"VER_SUITE_COMPUTE_SERVER=0x4000 };", 0);

	sdb_set (obj->kv, "mdmp_callback_type.cparse",
		"enum mdmp_type { ModuleCallback=0,"
		"ThreadCallback=1, ThreadExCallback=2, "
		"IncludeThreadCallback=3, IncludeModuleCallback=4, "
		"MemoryCallback=5, CancelCallback=6, "
		"WriteKernelMinidumpCallback=7, "
		"KernelMinidumpStatusCallback=8, "
		"RemoveMemoryCallback=9, "
		"IncludeVmRegionCallback=10, "
		"IoStartCallback=11, IoWriteAllCallback=12, "
		"IoFinishCallback=13, ReadMemoryFailureCallback=14, "
		"SecondaryFlagsCallback=15 };", 0);

	sdb_set (obj->kv, "mdmp_exception_code.cparse",
		"enum mdmp_exception_code { "
		"DBG_CONTROL_C=0x40010005, "
		"EXCEPTION_GUARD_PAGE_VIOLATION=0x80000001, "
		"EXCEPTION_DATATYPE_MISALIGNMENT=0x80000002, "
		"EXCEPTION_BREAKPOINT=0x80000003, "
		"EXCEPTION_SINGLE_STEP=0x80000004, "
		"EXCEPTION_ACCESS_VIOLATION=0xc0000005, "
		"EXCEPTION_IN_PAGE_ERROR=0xc0000006, "
		"EXCEPTION_INVALID_HANDLE=0xc0000008, "
		"EXCEPTION_ILLEGAL_INSTRUCTION=0xc000001d, "
		"EXCEPTION_NONCONTINUABLE_EXCEPTION=0xc0000025, "
		"EXCEPTION_INVALID_DISPOSITION=0xc0000026, "
		"EXCEPTION_ARRAY_BOUNDS_EXCEEDED=0xc000008c, "
		"EXCEPTION_FLOAT_DENORMAL_OPERAND=0xc000008d, "
		"EXCEPTION_FLOAT_DIVIDE_BY_ZERO=0xc000008e, "
		"EXCEPTION_FLOAT_INEXACT_RESULT=0xc000008f, "
		"EXCEPTION_FLOAT_INVALID_OPERATION=0xc0000090, "
		"EXCEPTION_FLOAT_OVERFLOW=0xc0000091, "
		"EXCEPTION_FLOAT_STACK_CHECK=0xc0000092, "
		"EXCEPTION_FLOAT_UNDERFLOW=0xc0000093, "
		"EXCEPTION_INTEGER_DIVIDE_BY_ZERO=0xc0000094, "
		"EXCEPTION_INTEGER_OVERFLOW=0xc0000095, "
		"EXCEPTION_PRIVILEGED_INSTRUCTION=0xc0000096, "
		"EXCEPTION_STACK_OVERFLOW=0xc00000fd, "
		"EXCEPTION_POSSIBLE_DEADLOCK=0xc0000194 };", 0);

	sdb_set (obj->kv, "mdmp_exception_flags.cparse",
		"enum mdmp_exception_flags { "
		"EXCEPTION_CONTINUABLE=0, "
		"EXCEPTION_NONCONTINUABLE=1 };", 0);

	sdb_set (obj->kv, "mdmp_handle_object_information_type.cparse",
		"enum mdmp_handle_object_information_type { "
		"MiniHandleObjectInformationNone=0, "
		"MiniThreadInformation1=1, MiniMutantInformation1=2, "
		"MiniMutantInformation2=3, MiniMutantProcessInformation1=4, "
		"MiniProcessInformation2=5 };", 0);

	sdb_set (obj->kv, "mdmp_secondary_flags.cparse",
		"enum mdmp_secondary_flags { "
		"MiniSecondaryWithoutPowerInfo=0 };", 0);

	sdb_set (obj->kv, "mdmp_stream_type.cparse",
		"enum mdmp_stream_type { UnusedStream=0, "
		"ReservedStream0=1, ReservedStream1=2, "
		"ThreadListStream=3, ModuleListStream=4, "
		"MemoryListStream=5, ExceptionStream=6, "
		"SystemInfoStream=7, ThreadExListStream=8, "
		"Memory64ListStream=9, CommentStreamA=10, "
		"CommentStreamW=11, HandleDataStream=12, "
		"FunctionTableStream=13, UnloadedModuleListStream=14, "
		"MiscInfoStream=15, MemoryInfoListStream=16, "
		"ThreadInfoListStream=17, "
		"HandleOperationListStream=18, "
		"LastReservedStream=0xffff };", 0);

	sdb_set (obj->kv, "mdmp_type.cparse", "enum mdmp_type { "
		"MiniDumpNormal=0x0, "
		"MiniDumpWithDataSegs=0x1, "
		"MiniDumpWithFullMemory=0x2, "
		"MiniDumpWithHandleData=0x4, "
		"MiniDumpFilterMemory=0x8, "
		"MiniDumpScanMemory=0x10, "
		"MiniDumpWithUnloadedModule=0x20, "
		"MiniDumpWihinDirectlyReferencedMemory=0x40, "
		"MiniDumpFilterWithModulePaths=0x80,"
		"MiniDumpWithProcessThreadData=0x100, "
		"MiniDumpWithPrivateReadWriteMemory=0x200, "
		"MiniDumpWithoutOptionalDate=0x400, "
		"MiniDumpWithFullMemoryInfo=0x800, "
		"MiniDumpWithThreadInfo=0x1000, "
		"MiniDumpWithCodeSegs=0x2000, "
		"MiniDumpWithoutAuxiliaryState=0x4000, "
		"MiniDumpWithFullAuxiliaryState=0x8000, "
		"MiniDumpWithPrivateWriteCopyMemory=0x10000, "
		"MiniDumpIgnoreInaccessibleMemory=0x20000, "
		"MiniDumpWithTokenInformation=0x40000, "
		"MiniDumpWithModuleHeaders=0x80000, "
		"MiniDumpFilterTriage=0x100000, "
		"MiniDumpValidTypeFlags=0x1fffff };", 0);

	sdb_set (obj->kv, "mdmp_module_write_flags.cparse",
		"enum mdmp_module_write_flags { "
		"ModuleWriteModule=0, ModuleWriteDataSeg=2, "
		"ModuleWriteMiscRecord=4, ModuleWriteCvRecord=8, "
		"ModuleReferencedByMemory=0x10, ModuleWriteTlsData=0x20, "
		"ModuleWriteCodeSegs=0x40 };", 0);

	sdb_set (obj->kv, "mdmp_thread_write_flags.cparse",
		"enum mdmp_thread_write_flags { "
		"ThreadWriteThread=0, ThreadWriteStack=2, "
		"ThreadWriteContext=4, ThreadWriteBackingStore=8, "
		"ThreadWriteInstructionWindow=0x10, "
		"ThreadWriteThreadData=0x20, "
		"ThreadWriteThreadInfo=0x40 };", 0);

	sdb_set (obj->kv, "mdmp_context_flags.cparse",
		"enum mdmp_context_flags { CONTEXT_i386=0x10000, "
		"CONTEXT_CONTROL=0x10001, CONTEXT_INTEGER=0x10002, "
		"CONTEXT_SEGMENTS=0x10004, CONTEXT_FLOATING_POINT=0x10008, "
		"CONTEXT_DEBUG_REGISTERS=0x10010, "
		"CONTEXT_EXTENDED_REGISTERS=0x10020 };", 0);

	sdb_set (obj->kv, "mdmp_location_descriptor.format",
		"dd DataSize RVA", 0);
	sdb_set (obj->kv, "mdmp_location_descriptor64.format",
		"qq DataSize RVA", 0);
	sdb_set (obj->kv, "mdmp_memory_descriptor.format", "q? "
		"StartOfMemoryRange "
		"(mdmp_location_descriptor)Memory", 0);
	sdb_set (obj->kv, "mdmp_memory_descriptor64.format", "qq "
		"StartOfMemoryRange DataSize", 0);

#if 0
	/* TODO: Flag dependent thus not fully implemented */
	sdb_set (obj->kv, "mdmp_context.format", "[4]B "
		"(mdmp_context_flags)ContextFlags", 0);
#endif

	sdb_set (obj->kv, "mdmp_vs_fixedfileinfo.format", "ddddddddddddd "
		"dwSignature dwStrucVersion dwFileVersionMs "
		"dwFileVersionLs dwProductVersionMs "
		"dwProductVersionLs dwFileFlagsMask dwFileFlags "
		"dwFileOs dwFileType dwFileSubtype dwFileDateMs "
		"dwFileDateLs", 0);

	sdb_set (obj->kv, "mdmp_string.format", "dZ Length Buffer", 0);
}