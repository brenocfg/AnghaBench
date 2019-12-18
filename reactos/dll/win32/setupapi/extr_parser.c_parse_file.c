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
typedef  int /*<<< orphan*/  utf8_bom ;
struct line {scalar_t__ nb_fields; int first_field; } ;
struct inf_file {int strings_section; struct field* fields; void* strings; void* string_pos; } ;
struct field {int /*<<< orphan*/  text; } ;
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int CP_ACP ; 
 int CP_UTF8 ; 
 int /*<<< orphan*/  Chicago ; 
 int /*<<< orphan*/  CreateFileMappingW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_WRONG_INF_STYLE ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int GetFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int INF_STYLE_WIN4 ; 
 void* MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  RtlIsTextUnicode (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  Signature ; 
 int /*<<< orphan*/  UnmapViewOfFile (void*) ; 
 int /*<<< orphan*/  Version ; 
 int /*<<< orphan*/  Windows95 ; 
 int /*<<< orphan*/  WindowsNT ; 
 struct line* find_line (struct inf_file*,int,int /*<<< orphan*/ ) ; 
 int find_section (struct inf_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_inf_file (struct inf_file*) ; 
 int /*<<< orphan*/  memcmp (void*,int const*,int) ; 
 int parse_buffer (struct inf_file*,int*,int*,int*) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inf_file *parse_file( HANDLE handle, UINT *error_line, DWORD style )
{
    void *buffer;
    DWORD err = 0;
    struct inf_file *file;

    DWORD size = GetFileSize( handle, NULL );
    HANDLE mapping = CreateFileMappingW( handle, NULL, PAGE_READONLY, 0, size, NULL );
    if (!mapping) return NULL;
    buffer = MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, size );
    NtClose( mapping );
    if (!buffer) return NULL;

    if (!(file = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*file) )))
    {
        err = ERROR_NOT_ENOUGH_MEMORY;
        goto done;
    }

    /* we won't need more strings space than the size of the file,
     * so we can preallocate it here
     */
    if (!(file->strings = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) )))
    {
        err = ERROR_NOT_ENOUGH_MEMORY;
        goto done;
    }
    file->string_pos = file->strings;
    file->strings_section = -1;

    if (!RtlIsTextUnicode( buffer, size, NULL ))
    {
        static const BYTE utf8_bom[3] = { 0xef, 0xbb, 0xbf };
        WCHAR *new_buff;
        UINT codepage = CP_ACP;
        UINT offset = 0;

        if (size > sizeof(utf8_bom) && !memcmp( buffer, utf8_bom, sizeof(utf8_bom) ))
        {
            codepage = CP_UTF8;
            offset = sizeof(utf8_bom);
        }

        if ((new_buff = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) )))
        {
            DWORD len = MultiByteToWideChar( codepage, 0, (char *)buffer + offset,
                                             size - offset, new_buff, size );
            err = parse_buffer( file, new_buff, new_buff + len, error_line );
            HeapFree( GetProcessHeap(), 0, new_buff );
        }
    }
    else
    {
        WCHAR *new_buff = buffer;
        /* UCS-16 files should start with the Unicode BOM; we should skip it */
        if (*new_buff == 0xfeff)
            new_buff++;
        err = parse_buffer( file, new_buff, (WCHAR *)((char *)buffer + size), error_line );
    }

    if (!err)  /* now check signature */
    {
        int version_index = find_section( file, Version );
        if (version_index != -1)
        {
            struct line *line = find_line( file, version_index, Signature );
            if (line && line->nb_fields > 0)
            {
                struct field *field = file->fields + line->first_field;
                if (!strcmpiW( field->text, Chicago )) goto done;
                if (!strcmpiW( field->text, WindowsNT )) goto done;
                if (!strcmpiW( field->text, Windows95 )) goto done;
            }
        }
        if (error_line) *error_line = 0;
        if (style & INF_STYLE_WIN4) err = ERROR_WRONG_INF_STYLE;
    }

 done:
    UnmapViewOfFile( buffer );
    if (err)
    {
        if (file) free_inf_file( file );
        SetLastError( err );
        file = NULL;
    }
    return file;
}