#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct resource_size_info {scalar_t__ total_size; } ;
struct mapping_info {scalar_t__ base; scalar_t__ size; } ;
typedef  char WCHAR ;
struct TYPE_23__ {scalar_t__ SectionAlignment; scalar_t__ FileAlignment; scalar_t__ SizeOfImage; scalar_t__ NumberOfRvaAndSizes; TYPE_3__* DataDirectory; void* SizeOfInitializedData; } ;
struct TYPE_27__ {TYPE_5__ OptionalHeader; } ;
struct TYPE_20__ {scalar_t__ VirtualSize; } ;
struct TYPE_26__ {int Characteristics; int VirtualAddress; scalar_t__ PointerToRawData; scalar_t__ SizeOfRawData; TYPE_2__ Misc; int /*<<< orphan*/  Name; } ;
struct TYPE_25__ {char* pFileName; int /*<<< orphan*/  bDeleteExistingResources; } ;
struct TYPE_24__ {scalar_t__ Magic; scalar_t__ SectionAlignment; scalar_t__ FileAlignment; scalar_t__ SizeOfImage; scalar_t__ NumberOfRvaAndSizes; TYPE_4__* DataDirectory; void* SizeOfInitializedData; } ;
struct TYPE_22__ {scalar_t__ VirtualAddress; scalar_t__ Size; } ;
struct TYPE_21__ {int VirtualAddress; scalar_t__ Size; } ;
struct TYPE_19__ {int /*<<< orphan*/  NumberOfSections; } ;
struct TYPE_18__ {TYPE_6__ OptionalHeader; TYPE_1__ FileHeader; } ;
typedef  TYPE_7__ QUEUEDUPDATES ;
typedef  int LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  TYPE_8__ IMAGE_SECTION_HEADER ;
typedef  TYPE_9__ IMAGE_NT_HEADERS64 ;
typedef  TYPE_10__ IMAGE_NT_HEADERS32 ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int CopyFileW (char*,char*,int) ; 
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 size_t IMAGE_DIRECTORY_ENTRY_RESOURCE ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 int IMAGE_SCN_CNT_INITIALIZED_DATA ; 
 int IMAGE_SCN_MEM_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int TRUE ; 
 struct mapping_info* create_mapping (char*,int) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  destroy_mapping (struct mapping_info*) ; 
 void* get_init_data_size (scalar_t__,scalar_t__) ; 
 scalar_t__ get_nt_header (scalar_t__,scalar_t__) ; 
 TYPE_8__* get_resource_section (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_resource_sizes (TYPE_7__*,struct resource_size_info*) ; 
 TYPE_8__* get_section_header (scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int read_mapped_resources (TYPE_7__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  res_write_padding (int /*<<< orphan*/ *,scalar_t__) ; 
 int resize_mapping (struct mapping_info*,scalar_t__) ; 
 int write_resources (TYPE_7__*,int /*<<< orphan*/ *,struct resource_size_info*,scalar_t__) ; 

__attribute__((used)) static BOOL write_raw_resources( QUEUEDUPDATES *updates )
{
    static const WCHAR prefix[] = { 'r','e','s','u',0 };
    WCHAR tempdir[MAX_PATH], tempfile[MAX_PATH];
    DWORD i, section_size;
    BOOL ret = FALSE;
    IMAGE_SECTION_HEADER *sec;
    IMAGE_NT_HEADERS32 *nt;
    IMAGE_NT_HEADERS64 *nt64;
    struct resource_size_info res_size;
    BYTE *res_base;
    struct mapping_info *read_map = NULL, *write_map = NULL;
    DWORD PeSectionAlignment, PeFileAlignment, PeSizeOfImage;

    /* copy the exe to a temp file then update the temp file... */
    tempdir[0] = 0;
    if (!GetTempPathW( MAX_PATH, tempdir ))
        return ret;

    if (!GetTempFileNameW( tempdir, prefix, 0, tempfile ))
        return ret;

    if (!CopyFileW( updates->pFileName, tempfile, FALSE ))
        goto done;

    TRACE("tempfile %s\n", debugstr_w(tempfile));

    if (!updates->bDeleteExistingResources)
    {
        read_map = create_mapping( updates->pFileName, FALSE );
        if (!read_map)
            goto done;

        ret = read_mapped_resources( updates, read_map->base, read_map->size );
        if (!ret)
        {
            ERR("failed to read existing resources\n");
            goto done;
        }
    }

    write_map = create_mapping( tempfile, TRUE );
    if (!write_map)
        goto done;

    nt = (IMAGE_NT_HEADERS32*)get_nt_header( write_map->base, write_map->size );
    if (!nt)
        goto done;

    nt64 = (IMAGE_NT_HEADERS64*)nt;
    if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        PeSectionAlignment = nt64->OptionalHeader.SectionAlignment;
        PeFileAlignment = nt64->OptionalHeader.FileAlignment;
        PeSizeOfImage = nt64->OptionalHeader.SizeOfImage;
    } else {
        PeSectionAlignment = nt->OptionalHeader.SectionAlignment;
        PeFileAlignment = nt->OptionalHeader.FileAlignment;
        PeSizeOfImage = nt->OptionalHeader.SizeOfImage;
    }

    if ((LONG)PeSectionAlignment <= 0)
    {
        ERR("invalid section alignment %08x\n", PeSectionAlignment);
        goto done;
    }

    if ((LONG)PeFileAlignment <= 0)
    {
        ERR("invalid file alignment %08x\n", PeFileAlignment);
        goto done;
    }

    sec = get_resource_section( write_map->base, write_map->size );
    if (!sec) /* no section, add one */
    {
        DWORD num_sections;

        sec = get_section_header( write_map->base, write_map->size, &num_sections );
        if (!sec)
            goto done;

        sec += num_sections;
        nt->FileHeader.NumberOfSections++;

        memset( sec, 0, sizeof *sec );
        memcpy( sec->Name, ".rsrc", 5 );
        sec->Characteristics = IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ;
        sec->VirtualAddress = PeSizeOfImage;
    }

    if (!sec->PointerToRawData)  /* empty section */
    {
        sec->PointerToRawData = write_map->size + (-write_map->size) % PeFileAlignment;
        sec->SizeOfRawData = 0;
    }

    TRACE("before .rsrc at %08x, size %08x\n", sec->PointerToRawData, sec->SizeOfRawData);

    get_resource_sizes( updates, &res_size );

    /* round up the section size */
    section_size = res_size.total_size;
    section_size += (-section_size) % PeFileAlignment;

    TRACE("requires %08x (%08x) bytes\n", res_size.total_size, section_size );

    /* check if the file size needs to be changed */
    if (section_size != sec->SizeOfRawData)
    {
        DWORD old_size = write_map->size;
        DWORD virtual_section_size = res_size.total_size + (-res_size.total_size) % PeSectionAlignment;
        int delta = section_size - (sec->SizeOfRawData + (-sec->SizeOfRawData) % PeFileAlignment);
        int rva_delta = virtual_section_size -
            (sec->Misc.VirtualSize + (-sec->Misc.VirtualSize) % PeSectionAlignment);
        /* when new section is added it could end past current mapping size */
        BOOL rsrc_is_last = sec->PointerToRawData + sec->SizeOfRawData >= old_size;
	/* align .rsrc size when possible */
        DWORD mapping_size = rsrc_is_last ? sec->PointerToRawData + section_size : old_size + delta;

        /* postpone file truncation if there are some data to be moved down from file end */
        BOOL resize_after = mapping_size < old_size && !rsrc_is_last;

        TRACE("file size %08x -> %08x\n", old_size, mapping_size);

        if (!resize_after)
        {
            /* unmap the file before changing the file size */
            ret = resize_mapping( write_map, mapping_size );

            /* get the pointers again - they might be different after remapping */
            nt = (IMAGE_NT_HEADERS32*)get_nt_header( write_map->base, mapping_size );
            if (!nt)
            {
                ERR("couldn't get NT header\n");
                goto done;
            }
            nt64 = (IMAGE_NT_HEADERS64*)nt;

            sec = get_resource_section( write_map->base, mapping_size );
            if (!sec)
                 goto done;
        }

        if (!rsrc_is_last) /* not last section, relocate trailing sections */
        {
            IMAGE_SECTION_HEADER *s;
            DWORD tail_start = sec->PointerToRawData + sec->SizeOfRawData;
            DWORD i, num_sections = 0;

            memmove( (char*)write_map->base + tail_start + delta, (char*)write_map->base + tail_start, old_size - tail_start );

            s = get_section_header( write_map->base, mapping_size, &num_sections );

            for (i=0; i<num_sections; i++)
            {
                if (s[i].PointerToRawData > sec->PointerToRawData)
                {
                    s[i].PointerToRawData += delta;
                    s[i].VirtualAddress += rva_delta;
                }
            }
        }

        if (resize_after)
        {
            ret = resize_mapping( write_map, mapping_size );

            nt = (IMAGE_NT_HEADERS32*)get_nt_header( write_map->base, mapping_size );
            if (!nt)
            {
                ERR("couldn't get NT header\n");
                goto done;
            }
            nt64 = (IMAGE_NT_HEADERS64*)nt;

            sec = get_resource_section( write_map->base, mapping_size );
            if (!sec)
                 goto done;
        }

        /* adjust the PE header information */
        sec->SizeOfRawData = section_size;
        sec->Misc.VirtualSize = virtual_section_size;
        if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
            nt64->OptionalHeader.SizeOfImage += rva_delta;
            nt64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress = sec->VirtualAddress;
            nt64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size = res_size.total_size;
            nt64->OptionalHeader.SizeOfInitializedData = get_init_data_size( write_map->base, mapping_size );

            for (i=0; i<nt64->OptionalHeader.NumberOfRvaAndSizes; i++)
                if (nt64->OptionalHeader.DataDirectory[i].VirtualAddress > sec->VirtualAddress)
                    nt64->OptionalHeader.DataDirectory[i].VirtualAddress += rva_delta;
        } else {
            nt->OptionalHeader.SizeOfImage += rva_delta;
            nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress = sec->VirtualAddress;
            nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size = res_size.total_size;
            nt->OptionalHeader.SizeOfInitializedData = get_init_data_size( write_map->base, mapping_size );

            for (i=0; i<nt->OptionalHeader.NumberOfRvaAndSizes; i++)
                if (nt->OptionalHeader.DataDirectory[i].VirtualAddress > sec->VirtualAddress)
                    nt->OptionalHeader.DataDirectory[i].VirtualAddress += rva_delta;
        }
    }

    res_base = (LPBYTE) write_map->base + sec->PointerToRawData;

    TRACE("base = %p offset = %08x\n", write_map->base, sec->PointerToRawData);

    ret = write_resources( updates, res_base, &res_size, sec->VirtualAddress );

    res_write_padding( res_base + res_size.total_size, section_size - res_size.total_size );

    TRACE("after  .rsrc at %08x, size %08x\n", sec->PointerToRawData, sec->SizeOfRawData);

done:
    destroy_mapping( read_map );
    destroy_mapping( write_map );

    if (ret)
        ret = CopyFileW( tempfile, updates->pFileName, FALSE );

    DeleteFileW( tempfile );

    return ret;
}