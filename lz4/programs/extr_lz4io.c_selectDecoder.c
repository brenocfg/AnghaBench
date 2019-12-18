#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dRess_t ;
struct TYPE_6__ {int /*<<< orphan*/  passThrough; int /*<<< orphan*/  overwrite; int /*<<< orphan*/  testMode; } ;
typedef  TYPE_1__ LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 unsigned long long ENDOFSTREAM ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/  EXTENDED_FORMAT ; 
#define  LEGACY_MAGICNUMBER 130 
#define  LZ4IO_MAGICNUMBER 129 
#define  LZ4IO_SKIPPABLE0 128 
 unsigned long long LZ4IO_decodeLegacyStream (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long long LZ4IO_decompressLZ4F (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LZ4IO_isSkippableMagicNumber (unsigned int) ; 
 unsigned long long LZ4IO_passThrough (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 
 void* LZ4IO_readLE32 (unsigned char*) ; 
 int MAGICNUMBER_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int fseek_u32 (int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int g_magicRead ; 

__attribute__((used)) static unsigned long long selectDecoder(LZ4IO_prefs_t* const prefs, dRess_t ress, FILE* finput, FILE* foutput)
{
    unsigned char MNstore[MAGICNUMBER_SIZE];
    unsigned magicNumber;
    static unsigned nbFrames = 0;

    /* init */
    nbFrames++;

    /* Check Archive Header */
    if (g_magicRead) {  /* magic number already read from finput (see legacy frame)*/
        magicNumber = g_magicRead;
        g_magicRead = 0;
    } else {
        size_t const nbReadBytes = fread(MNstore, 1, MAGICNUMBER_SIZE, finput);
        if (nbReadBytes==0) { nbFrames = 0; return ENDOFSTREAM; }   /* EOF */
        if (nbReadBytes != MAGICNUMBER_SIZE)
          EXM_THROW(40, "Unrecognized header : Magic Number unreadable");
        magicNumber = LZ4IO_readLE32(MNstore);   /* Little Endian format */
    }
    if (LZ4IO_isSkippableMagicNumber(magicNumber))
        magicNumber = LZ4IO_SKIPPABLE0;   /* fold skippable magic numbers */

    switch(magicNumber)
    {
    case LZ4IO_MAGICNUMBER:
        return LZ4IO_decompressLZ4F(prefs, ress, finput, foutput);
    case LEGACY_MAGICNUMBER:
        DISPLAYLEVEL(4, "Detected : Legacy format \n");
        return LZ4IO_decodeLegacyStream(prefs, finput, foutput);
    case LZ4IO_SKIPPABLE0:
        DISPLAYLEVEL(4, "Skipping detected skippable area \n");
        {   size_t const nbReadBytes = fread(MNstore, 1, 4, finput);
            if (nbReadBytes != 4)
                EXM_THROW(42, "Stream error : skippable size unreadable");
        }
        {   unsigned const size = LZ4IO_readLE32(MNstore);
            int const errorNb = fseek_u32(finput, size, SEEK_CUR);
            if (errorNb != 0)
                EXM_THROW(43, "Stream error : cannot skip skippable area");
        }
        return 0;
    EXTENDED_FORMAT;  /* macro extension for custom formats */
    default:
        if (nbFrames == 1) {  /* just started */
            /* Wrong magic number at the beginning of 1st stream */
            if (!prefs->testMode && prefs->overwrite && prefs->passThrough) {
                nbFrames = 0;
                return LZ4IO_passThrough(prefs, finput, foutput, MNstore);
            }
            EXM_THROW(44,"Unrecognized header : file cannot be decoded");
        }
        {   long int const position = ftell(finput);  /* only works for files < 2 GB */
            DISPLAYLEVEL(2, "Stream followed by undecodable data ");
            if (position != -1L)
                DISPLAYLEVEL(2, "at position %i ", (int)position);
            DISPLAYLEVEL(2, "\n");
        }
        return ENDOFSTREAM;
    }
}