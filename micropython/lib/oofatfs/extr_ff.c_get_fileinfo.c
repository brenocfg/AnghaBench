#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  size_t UINT ;
struct TYPE_8__ {TYPE_3__* fs; } ;
struct TYPE_11__ {scalar_t__ sect; int blk_ofs; scalar_t__* dir; TYPE_1__ obj; } ;
struct TYPE_10__ {scalar_t__ fs_type; scalar_t__* lfnbuf; int /*<<< orphan*/  dirbuf; } ;
struct TYPE_9__ {char* fname; char* altname; int fattrib; void* fdate; void* ftime; int /*<<< orphan*/  fsize; } ;
typedef  char TCHAR ;
typedef  TYPE_2__ FILINFO ;
typedef  TYPE_3__ FATFS ;
typedef  int DWORD ;
typedef  TYPE_4__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CODEPAGE ; 
 void* DDEM ; 
 size_t DIR_Attr ; 
 int DIR_FileSize ; 
 int DIR_ModTime ; 
 size_t DIR_NTres ; 
 size_t FF_LFN_BUF ; 
 size_t FF_SFN_BUF ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ IsSurrogate (scalar_t__) ; 
 scalar_t__ IsUpper (scalar_t__) ; 
 int NS_BODY ; 
 int NS_EXT ; 
 scalar_t__ RDDEM ; 
 scalar_t__ dbc_1st (int) ; 
 scalar_t__ dbc_2nd (scalar_t__) ; 
 scalar_t__ ff_oem2uni (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_xfileinfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ld_dword (int*) ; 
 void* ld_word (int*) ; 
 scalar_t__ put_utf (scalar_t__,char*,size_t) ; 

__attribute__((used)) static void get_fileinfo (
    DIR* dp,            /* Pointer to the directory object */
    FILINFO* fno        /* Pointer to the file information to be filled */
)
{
    UINT si, di;
#if FF_USE_LFN
    BYTE lcf;
    WCHAR wc, hs;
    FATFS *fs = dp->obj.fs;
#else
    TCHAR c;
#endif


    fno->fname[0] = 0;          /* Invaidate file info */
    if (dp->sect == 0) return;  /* Exit if read pointer has reached end of directory */

#if FF_USE_LFN      /* LFN configuration */
#if FF_FS_EXFAT
    if (fs->fs_type == FS_EXFAT) {  /* On the exFAT volume */
        get_xfileinfo(fs->dirbuf, fno);
        return;
    } else
#endif
    {   /* On the FAT/FAT32 volume */
        if (dp->blk_ofs != 0xFFFFFFFF) {    /* Get LFN if available */
            si = di = hs = 0;
            while (fs->lfnbuf[si] != 0) {
                wc = fs->lfnbuf[si++];      /* Get an LFN character (UTF-16) */
                if (hs == 0 && IsSurrogate(wc)) {   /* Is it a surrogate? */
                    hs = wc; continue;      /* Get low surrogate */
                }
                wc = put_utf((DWORD)hs << 16 | wc, &fno->fname[di], FF_LFN_BUF - di);   /* Store it in UTF-16 or UTF-8 encoding */
                if (wc == 0) { di = 0; break; } /* Invalid char or buffer overflow? */
                di += wc;
                hs = 0;
            }
            if (hs != 0) di = 0;    /* Broken surrogate pair? */
            fno->fname[di] = 0;     /* Terminate the LFN (null string means LFN is invalid) */
        }
    }

    si = di = 0;
    while (si < 11) {       /* Get SFN from SFN entry */
        wc = dp->dir[si++];         /* Get a char */
        if (wc == ' ') continue;    /* Skip padding spaces */
        if (wc == RDDEM) wc = DDEM; /* Restore replaced DDEM character */
        if (si == 9 && di < FF_SFN_BUF) fno->altname[di++] = '.';   /* Insert a . if extension is exist */
#if FF_LFN_UNICODE >= 1 /* Unicode output */
        if (dbc_1st((BYTE)wc) && si != 8 && si != 11 && dbc_2nd(dp->dir[si])) { /* Make a DBC if needed */
            wc = wc << 8 | dp->dir[si++];
        }
        wc = ff_oem2uni(wc, CODEPAGE);      /* ANSI/OEM -> Unicode */
        if (wc == 0) { di = 0; break; }     /* Wrong char in the current code page? */
        wc = put_utf(wc, &fno->altname[di], FF_SFN_BUF - di);   /* Store it in Unicode */
        if (wc == 0) { di = 0; break; }     /* Buffer overflow? */
        di += wc;
#else                   /* ANSI/OEM output */
        fno->altname[di++] = (TCHAR)wc; /* Store it without any conversion */
#endif
    }
    fno->altname[di] = 0;   /* Terminate the SFN  (null string means SFN is invalid) */

    if (fno->fname[0] == 0) {   /* If LFN is invalid, altname[] needs to be copied to fname[] */
        if (di == 0) {  /* If LFN and SFN both are invalid, this object is inaccesible */
            fno->fname[di++] = '?';
        } else {
            for (si = di = 0, lcf = NS_BODY; fno->altname[si]; si++, di++) { /* Copy altname[] to fname[] with case information */
                wc = (WCHAR)fno->altname[si];
                if (wc == '.') lcf = NS_EXT;
                if (IsUpper(wc) && (dp->dir[DIR_NTres] & lcf)) wc += 0x20;
                fno->fname[di] = (TCHAR)wc;
            }
        }
        fno->fname[di] = 0; /* Terminate the LFN */
        if (!dp->dir[DIR_NTres]) fno->altname[0] = 0;   /* Altname is not needed if neither LFN nor case info is exist. */
    }

#else   /* Non-LFN configuration */
    si = di = 0;
    while (si < 11) {       /* Copy name body and extension */
        c = (TCHAR)dp->dir[si++];
        if (c == ' ') continue;     /* Skip padding spaces */
        if (c == RDDEM) c = DDEM;   /* Restore replaced DDEM character */
        if (si == 9) fno->fname[di++] = '.';/* Insert a . if extension is exist */
        fno->fname[di++] = c;
    }
    fno->fname[di] = 0;
#endif

    fno->fattrib = dp->dir[DIR_Attr];                   /* Attribute */
    fno->fsize = ld_dword(dp->dir + DIR_FileSize);      /* Size */
    fno->ftime = ld_word(dp->dir + DIR_ModTime + 0);    /* Time */
    fno->fdate = ld_word(dp->dir + DIR_ModTime + 2);    /* Date */
}