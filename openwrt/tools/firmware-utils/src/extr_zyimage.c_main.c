#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct signature   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sign ;
typedef  int /*<<< orphan*/  oldsign ;
struct signature {char const* magic; unsigned int device_id; char* firmware_version; unsigned int crc32; } ;
struct TYPE_5__ {char* member_0; } ;
struct TYPE_4__ {char member_0; char member_1; char member_2; char member_3; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 unsigned int atoi (int /*<<< orphan*/ *) ; 
 int chksum_crc32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chksum_crc32gentab () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (struct signature*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/ * optarg ; 
 size_t optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[]) {
  struct signature
  {
    const char magic[4];
    unsigned int device_id;
    char firmware_version[48];
    unsigned int crc32;
  }
  sign =
  {
    { 'Z', 'N', 'B', 'G' },
    1,
    { "V.1.0.0(1.0.0)" },
    0
  };
  FILE *f;
  struct signature oldsign;
  char *filename;
  static const char *optString;
  int opt;

  if (argc < 1)
    usage(argv[0]);

  optString = "v:d:h";
  opt = getopt( argc, argv, optString );
  while( opt != -1 ) {
    switch( opt ) {
      case 'v':
        if (optarg == NULL)
          usage(argv[0]);
        strncpy(sign.firmware_version, optarg, sizeof(sign.firmware_version)-1);
       sign.firmware_version[sizeof(sign.firmware_version)-1]='\0'; /* Make sure that string is terminated correctly */
        break;

      case 'd':
        sign.device_id = atoi(optarg);
        if (sign.device_id == 0)
          sign.device_id = (int)strtol(optarg, NULL, 16);
        break;

      case '?':
      case 'h':
        usage(argv[0]);
        break;

      default:
        break;
    }

    opt = getopt( argc, argv, optString );
  }

  chksum_crc32gentab();

  filename=argv[optind];
  if (access(filename, W_OK) || access(filename, R_OK))
  {
    printf("Not open input file %s\n", filename);
    exit(1);
  }
  f = fopen(argv[optind], "r+");
  if (f != NULL)
  {
    fseek(f, sizeof(sign)*-1, SEEK_END);
    fread(&oldsign, sizeof(oldsign), 1, f);

    if (strncmp(oldsign.magic,"ZNBG", sizeof(oldsign.magic)) == 0 )
    {
      printf("Image is already signed as:\nDevice ID: 0x%08x\nFirmware version: %s\nImage CRC32: 0x%x\n", oldsign.device_id, oldsign.firmware_version, oldsign.crc32);
      exit(0);
    }

    fseek(f, 0, SEEK_SET);
    sign.crc32 = chksum_crc32(f);
    fwrite(&sign, sizeof(sign), 1, f);
    fclose(f);

    printf("Image signed as:\nDevice ID: 0x%08x\nFirmware version: %s\nImage CRC32: 0x%x\n", sign.device_id, sign.firmware_version, sign.crc32);
  }
  return 0;
}