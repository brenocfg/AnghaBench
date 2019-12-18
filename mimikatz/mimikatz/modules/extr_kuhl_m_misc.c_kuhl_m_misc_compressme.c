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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIMIKATZ_COMPRESSED_FILENAME ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/ * _wpgmptr ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ kull_m_file_writeData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kull_m_memory_quick_compress (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

NTSTATUS kuhl_m_misc_compressme(int argc, wchar_t * argv[])
{
	PBYTE data, compressedData;
	DWORD size, compressedSize;
#pragma warning(push)
#pragma warning(disable:4996)
	wchar_t *fileName = _wpgmptr;
#pragma warning(pop)
	kprintf(L"Using \'%s\' as input file\n", fileName);
	if(kull_m_file_readData(fileName, &data, &size))
	{
		kprintf(L" * Original size  : %u\n", size);
		if(kull_m_memory_quick_compress(data, size, (PVOID *) &compressedData, &compressedSize))
		{
			kprintf(L" * Compressed size: %u (%.2f%%)\nUsing \'%s\' as output file... ", compressedSize, 100 * ((float) compressedSize / (float) size), MIMIKATZ_COMPRESSED_FILENAME);
			if(kull_m_file_writeData(MIMIKATZ_COMPRESSED_FILENAME, compressedData, compressedSize))
				kprintf(L"OK!\n");
			else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
			LocalFree(compressedData);
		}
		LocalFree(data);
	}
	return STATUS_SUCCESS;
}