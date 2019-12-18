#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_3__ {int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,char const*) ; 
#define  TIFFReadDirEntryErrAlloc 134 
#define  TIFFReadDirEntryErrCount 133 
#define  TIFFReadDirEntryErrIo 132 
#define  TIFFReadDirEntryErrPsdif 131 
#define  TIFFReadDirEntryErrRange 130 
#define  TIFFReadDirEntryErrSizesan 129 
#define  TIFFReadDirEntryErrType 128 
 int /*<<< orphan*/  TIFFWarningExt (int /*<<< orphan*/ ,char const*,char*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TIFFReadDirEntryOutputErr(TIFF* tif, enum TIFFReadDirEntryErr err, const char* module, const char* tagname, int recover)
{
	if (!recover) {
		switch (err) {
			case TIFFReadDirEntryErrCount:
				TIFFErrorExt(tif->tif_clientdata, module,
					     "Incorrect count for \"%s\"",
					     tagname);
				break;
			case TIFFReadDirEntryErrType:
				TIFFErrorExt(tif->tif_clientdata, module,
					     "Incompatible type for \"%s\"",
					     tagname);
				break;
			case TIFFReadDirEntryErrIo:
				TIFFErrorExt(tif->tif_clientdata, module,
					     "IO error during reading of \"%s\"",
					     tagname);
				break;
			case TIFFReadDirEntryErrRange:
				TIFFErrorExt(tif->tif_clientdata, module,
					     "Incorrect value for \"%s\"",
					     tagname);
				break;
			case TIFFReadDirEntryErrPsdif:
				TIFFErrorExt(tif->tif_clientdata, module,
			"Cannot handle different values per sample for \"%s\"",
					     tagname);
				break;
			case TIFFReadDirEntryErrSizesan:
				TIFFErrorExt(tif->tif_clientdata, module,
				"Sanity check on size of \"%s\" value failed",
					     tagname);
				break;
			case TIFFReadDirEntryErrAlloc:
				TIFFErrorExt(tif->tif_clientdata, module,
					     "Out of memory reading of \"%s\"",
					     tagname);
				break;
			default:
				assert(0);   /* we should never get here */
				break;
		}
	} else {
		switch (err) {
			case TIFFReadDirEntryErrCount:
				TIFFWarningExt(tif->tif_clientdata, module,
				"Incorrect count for \"%s\"; tag ignored",
					     tagname);
				break;
			case TIFFReadDirEntryErrType:
				TIFFWarningExt(tif->tif_clientdata, module,
				"Incompatible type for \"%s\"; tag ignored",
					       tagname);
				break;
			case TIFFReadDirEntryErrIo:
				TIFFWarningExt(tif->tif_clientdata, module,
			"IO error during reading of \"%s\"; tag ignored",
					       tagname);
				break;
			case TIFFReadDirEntryErrRange:
				TIFFWarningExt(tif->tif_clientdata, module,
				"Incorrect value for \"%s\"; tag ignored",
					       tagname);
				break;
			case TIFFReadDirEntryErrPsdif:
				TIFFWarningExt(tif->tif_clientdata, module,
	"Cannot handle different values per sample for \"%s\"; tag ignored",
					       tagname);
				break;
			case TIFFReadDirEntryErrSizesan:
				TIFFWarningExt(tif->tif_clientdata, module,
		"Sanity check on size of \"%s\" value failed; tag ignored",
					       tagname);
				break;
			case TIFFReadDirEntryErrAlloc:
				TIFFWarningExt(tif->tif_clientdata, module,
				"Out of memory reading of \"%s\"; tag ignored",
					       tagname);
				break;
			default:
				assert(0);   /* we should never get here */
				break;
		}
	}
}