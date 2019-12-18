#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stat_t ;
typedef  int /*<<< orphan*/  prefs ;
struct TYPE_12__ {void* srcBuffer; void* dstBuffer; size_t dstBufferSize; int /*<<< orphan*/  cdict; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ cRess_t ;
typedef  scalar_t__ U64 ;
struct TYPE_11__ {scalar_t__ contentSize; scalar_t__ contentChecksumFlag; scalar_t__ blockChecksumFlag; scalar_t__ blockSizeID; scalar_t__ blockMode; } ;
struct TYPE_14__ {int autoFlush; int compressionLevel; TYPE_1__ frameInfo; int /*<<< orphan*/  favorDecSpeed; } ;
struct TYPE_13__ {size_t blockSize; scalar_t__ removeSrcFile; scalar_t__ contentSizeFlag; int /*<<< orphan*/  favorDecSpeed; scalar_t__ streamChecksum; scalar_t__ blockChecksum; scalar_t__ blockSizeId; scalar_t__ blockIndependence; } ;
typedef  TYPE_3__ LZ4IO_prefs_t ;
typedef  TYPE_4__ LZ4F_preferences_t ;
typedef  scalar_t__ LZ4F_contentChecksum_t ;
typedef  int /*<<< orphan*/  LZ4F_compressionContext_t ;
typedef  scalar_t__ LZ4F_blockSizeID_t ;
typedef  scalar_t__ LZ4F_blockMode_t ;
typedef  scalar_t__ LZ4F_blockChecksum_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  DISPLAYUPDATE (int,char*,unsigned int,double) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 size_t LZ4F_compressBegin_usingCDict (int /*<<< orphan*/ ,void* const,size_t const,int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t LZ4F_compressEnd (int /*<<< orphan*/ ,void* const,size_t const,int /*<<< orphan*/ *) ; 
 size_t LZ4F_compressFrame_usingCDict (int /*<<< orphan*/ ,void* const,size_t const,void* const,size_t,int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t LZ4F_compressUpdate (int /*<<< orphan*/ ,void* const,size_t const,void* const,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (size_t) ; 
 scalar_t__ LZ4F_isError (size_t) ; 
 int /*<<< orphan*/ * LZ4IO_openDstFile (TYPE_3__* const,char const*) ; 
 int /*<<< orphan*/ * LZ4IO_openSrcFile (char const*) ; 
 scalar_t__ UTIL_getFileSize (char const*) ; 
 scalar_t__ UTIL_getFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTIL_setFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (void* const,size_t,size_t const,int /*<<< orphan*/ *) ; 
 size_t fwrite (void* const,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nulmark ; 
 scalar_t__ remove (char const*) ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
LZ4IO_compressFilename_extRess(LZ4IO_prefs_t* const io_prefs, cRess_t ress,
                               const char* srcFileName, const char* dstFileName,
                               int compressionLevel)
{
    unsigned long long filesize = 0;
    unsigned long long compressedfilesize = 0;
    FILE* srcFile;
    FILE* dstFile;
    void* const srcBuffer = ress.srcBuffer;
    void* const dstBuffer = ress.dstBuffer;
    const size_t dstBufferSize = ress.dstBufferSize;
    const size_t blockSize = io_prefs->blockSize;
    size_t readSize;
    LZ4F_compressionContext_t ctx = ress.ctx;   /* just a pointer */
    LZ4F_preferences_t prefs;

    /* Init */
    srcFile = LZ4IO_openSrcFile(srcFileName);
    if (srcFile == NULL) return 1;
    dstFile = LZ4IO_openDstFile(io_prefs, dstFileName);
    if (dstFile == NULL) { fclose(srcFile); return 1; }
    memset(&prefs, 0, sizeof(prefs));


    /* Set compression parameters */
    prefs.autoFlush = 1;
    prefs.compressionLevel = compressionLevel;
    prefs.frameInfo.blockMode = (LZ4F_blockMode_t)io_prefs->blockIndependence;
    prefs.frameInfo.blockSizeID = (LZ4F_blockSizeID_t)io_prefs->blockSizeId;
    prefs.frameInfo.blockChecksumFlag = (LZ4F_blockChecksum_t)io_prefs->blockChecksum;
    prefs.frameInfo.contentChecksumFlag = (LZ4F_contentChecksum_t)io_prefs->streamChecksum;
    prefs.favorDecSpeed = io_prefs->favorDecSpeed;
    if (io_prefs->contentSizeFlag) {
      U64 const fileSize = UTIL_getFileSize(srcFileName);
      prefs.frameInfo.contentSize = fileSize;   /* == 0 if input == stdin */
      if (fileSize==0)
          DISPLAYLEVEL(3, "Warning : cannot determine input content size \n");
    }

    /* read first block */
    readSize  = fread(srcBuffer, (size_t)1, blockSize, srcFile);
    if (ferror(srcFile)) EXM_THROW(30, "Error reading %s ", srcFileName);
    filesize += readSize;

    /* single-block file */
    if (readSize < blockSize) {
        /* Compress in single pass */
        size_t cSize = LZ4F_compressFrame_usingCDict(ctx, dstBuffer, dstBufferSize, srcBuffer, readSize, ress.cdict, &prefs);
        if (LZ4F_isError(cSize)) EXM_THROW(31, "Compression failed : %s", LZ4F_getErrorName(cSize));
        compressedfilesize = cSize;
        DISPLAYUPDATE(2, "\rRead : %u MB   ==> %.2f%%   ",
                      (unsigned)(filesize>>20), (double)compressedfilesize/(filesize+!filesize)*100);   /* avoid division by zero */

        /* Write Block */
        {   size_t const sizeCheck = fwrite(dstBuffer, 1, cSize, dstFile);
            if (sizeCheck!=cSize) EXM_THROW(32, "Write error : cannot write compressed block");
    }   }

    else

    /* multiple-blocks file */
    {
        /* Write Archive Header */
        size_t headerSize = LZ4F_compressBegin_usingCDict(ctx, dstBuffer, dstBufferSize, ress.cdict, &prefs);
        if (LZ4F_isError(headerSize)) EXM_THROW(33, "File header generation failed : %s", LZ4F_getErrorName(headerSize));
        { size_t const sizeCheck = fwrite(dstBuffer, 1, headerSize, dstFile);
          if (sizeCheck!=headerSize) EXM_THROW(34, "Write error : cannot write header"); }
        compressedfilesize += headerSize;

        /* Main Loop */
        while (readSize>0) {
            size_t outSize;

            /* Compress Block */
            outSize = LZ4F_compressUpdate(ctx, dstBuffer, dstBufferSize, srcBuffer, readSize, NULL);
            if (LZ4F_isError(outSize)) EXM_THROW(35, "Compression failed : %s", LZ4F_getErrorName(outSize));
            compressedfilesize += outSize;
            DISPLAYUPDATE(2, "\rRead : %u MB   ==> %.2f%%   ", (unsigned)(filesize>>20), (double)compressedfilesize/filesize*100);

            /* Write Block */
            { size_t const sizeCheck = fwrite(dstBuffer, 1, outSize, dstFile);
              if (sizeCheck!=outSize) EXM_THROW(36, "Write error : cannot write compressed block"); }

            /* Read next block */
            readSize  = fread(srcBuffer, (size_t)1, (size_t)blockSize, srcFile);
            filesize += readSize;
        }
        if (ferror(srcFile)) EXM_THROW(37, "Error reading %s ", srcFileName);

        /* End of Stream mark */
        headerSize = LZ4F_compressEnd(ctx, dstBuffer, dstBufferSize, NULL);
        if (LZ4F_isError(headerSize)) EXM_THROW(38, "End of file generation failed : %s", LZ4F_getErrorName(headerSize));

        { size_t const sizeCheck = fwrite(dstBuffer, 1, headerSize, dstFile);
          if (sizeCheck!=headerSize) EXM_THROW(39, "Write error : cannot write end of stream"); }
        compressedfilesize += headerSize;
    }

    /* Release file handlers */
    fclose (srcFile);
    if (strcmp(dstFileName,stdoutmark)) fclose (dstFile);   /* do not close stdout */

    /* Copy owner, file permissions and modification time */
    {   stat_t statbuf;
        if (strcmp (srcFileName, stdinmark)
         && strcmp (dstFileName, stdoutmark)
         && strcmp (dstFileName, nulmark)
         && UTIL_getFileStat(srcFileName, &statbuf)) {
            UTIL_setFileStat(dstFileName, &statbuf);
    }   }

    if (io_prefs->removeSrcFile) {  /* remove source file : --rm */
        if (remove(srcFileName))
            EXM_THROW(40, "Remove error : %s: %s", srcFileName, strerror(errno));
    }

    /* Final Status */
    DISPLAYLEVEL(2, "\r%79s\r", "");
    DISPLAYLEVEL(2, "Compressed %llu bytes into %llu bytes ==> %.2f%%\n",
                    filesize, compressedfilesize,
                    (double)compressedfilesize / (filesize + !filesize /* avoid division by zero */ ) * 100);

    return 0;
}